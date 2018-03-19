#!/bin/bash

rsync -aP html index.html manual.html style.css \
      $USER@web.sourceforge.net:/home/project-web/tclap/htdocs
