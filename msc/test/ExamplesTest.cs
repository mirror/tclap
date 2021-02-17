using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
//using System.Runtime.InteropServices.ComTypes;
using System.Text.RegularExpressions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace tclap.test
{
  [TestClass]
  public class ExamplesTest
  {
    private static string RunProcess(string name, string arguments)
    {
      using (var p = new Process())
      {
        var desc = new ProcessStartInfo(name)
        {
          Arguments = arguments,
          RedirectStandardInput = true,
          RedirectStandardOutput = true,
          RedirectStandardError = true,
          UseShellExecute = false
        };
        p.StartInfo = desc;
        p.Start();
        var output = p.StandardOutput.ReadLine();

        if (null == output)
        {
          output = p.StandardError.ReadLine();
        }

        if (null == output)
        {
          output = string.Empty;
        }

        if (output.StartsWith("PARSE ERROR"))
        {
          // TODO Check the while multiline text
          output = "PARSE ERROR ...";
        }
        return output;
      }
    }

    //[TestMethod]
    //public void TestExample1()
    //{
    //  string testProg = @"..\..\..\examples\Release\test1.exe";
    //  string testOutput = RunProcess(testProg, "-r -n mike");
    //  Assert.AreEqual("My name (spelled backwards) is: ekim", testOutput,
    //    "The test output is unexpected: {0}", testOutput);
    //}

    //[DataRow("test1", "-r -n mike", "My name (spelled backwards) is: ekim")]
    //[DataRow("test1", "-n mike", "My name is: mike")]
    //[DataTestMethod]
    //public void TestExample(string testHelper, string testArgs, string expectedOutput)
    //{
    //  string testProg = @"..\..\..\examples\Release\" + testHelper + ".exe";
    //  string testOutput = RunProcess(testProg, testArgs);
    //  Assert.AreEqual(expectedOutput, testOutput,
    //    "The test output is unexpected: {0}", testOutput);
    //}

    private static IEnumerable<string[]> GetExamplesData()
    {
      foreach (var testScriptFile in Directory.GetFiles(@"..\..\..\..\tests", "test*.sh"))
      {
        var testHelper = string.Empty;
        var testArgs = string.Empty;
        var expectedOutput = string.Empty;
        var isInconclusive = false;

        // Exceptional test scripts, which do not match the pattern below
        if (testScriptFile.EndsWith("testCheck.sh"))
        {
          continue;
        }

        using (var stream = new StreamReader(testScriptFile))
        {
          string line;
          while ((line = stream.ReadLine()) != null)
          {
            var matches = Regex.Matches(line, @"(test\d+)(?:\s?$| .*?(?:([-~\/].+$)|>.*$))");
            if (0 < matches.Count && 1 < matches[0].Groups.Count)
            {
              testHelper = matches[0].Groups[1].Value;
              var helperMatches = Regex.Matches(testHelper, "test[1-8]$");
              if (0 == helperMatches.Count)
              {
                // TODO Only tests using the first 8 helper programs are supported yet
                isInconclusive = true;
              }
            }
            if (0 < matches.Count && 2 < matches[0].Groups.Count)
            {
              testArgs = matches[0].Groups[2].Value;
            }
          }
        }

        var testOutFile = testScriptFile.Replace(".sh", ".out");
        using (var stream = new StreamReader(testOutFile))
        {
          expectedOutput = stream.ReadLine();
          if (expectedOutput.StartsWith("PARSE ERROR"))
          {
            // TODO Compare the whole multiline text
            expectedOutput = "PARSE ERROR ...";
          }
        }

        if (isInconclusive)
        {
          yield return new[] { "Inconclusive", "", "" };
        }
        else
        {
          yield return new[] { testHelper, testArgs, expectedOutput };
        }
        isInconclusive = false;
      }
    }

    [DataTestMethod]
    [DynamicData(nameof(GetExamplesData), DynamicDataSourceType.Method)]
    public void TestExamples(string testHelper, string testArgs, string expectedOutput)
    {
      if ("Inconclusive" == testHelper)
      {
        Assert.Inconclusive("Only tests using the first 8 helper programs are supported yet");
      }

      var testProg = @"..\..\..\examples\Release\" + testHelper + ".exe";
      var testOutput = RunProcess(testProg, testArgs);
      Assert.AreEqual(expectedOutput, testOutput,
        "The test output is unexpected: {0}", testOutput);
    }
  }
}
