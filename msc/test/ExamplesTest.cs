using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices.ComTypes;
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
          UseShellExecute = false
        };
        p.StartInfo = desc;
        p.Start();
        return p.StandardOutput.ReadLine();
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

        if (testScriptFile.EndsWith("testCheck.sh"))
        {
          continue;
        }

        using (var stream = new StreamReader(testScriptFile))
        {
          string line;
          while ((line = stream.ReadLine()) != null)
          {
            var matches = Regex.Matches(line, @"(test\d+) .*(-.+$)");
            if (0 < matches.Count && 2 < matches[0].Groups.Count)
            {
              testHelper = matches[0].Groups[1].Value;
              testArgs = matches[0].Groups[2].Value;
            }
          }
        }

        var testOutFile = testScriptFile.Replace(".sh", ".out");
        using (var stream = new StreamReader(testOutFile))
        {
          expectedOutput = stream.ReadLine();
        }

        yield return new[] { testHelper, testArgs, expectedOutput };
      }
    }

    [DataTestMethod]
    [DynamicData(nameof(GetExamplesData), DynamicDataSourceType.Method)]
    public void TestExamples(string testHelper, string testArgs, string expectedOutput)
    {
      var testProg = @"..\..\..\examples\Release\" + testHelper + ".exe";
      var testOutput = RunProcess(testProg, testArgs);
      Assert.AreEqual(expectedOutput, testOutput,
        "The test output is unexpected: {0}", testOutput);
    }
  }
}
