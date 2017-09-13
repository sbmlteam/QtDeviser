; This file installs the sbmlpkgspec version needed for deviser

Section sbmlpkgspec
  SetOverwrite ifnewer
  SetOutPath "$INSTDIR\sbmlpkgspec"
  File "dist\sbmlpkgspec\AUTHORS.txt"
  File "dist\sbmlpkgspec\COPYING.html"
  File "dist\sbmlpkgspec\COPYING.txt"
  File "dist\sbmlpkgspec\LICENSE.html"
  File "dist\sbmlpkgspec\LICENSE.txt"
  SetOutPath "$INSTDIR\sbmlpkgspec\logos"
  File "dist\sbmlpkgspec\logos\sbml-badge.eps"
  File "dist\sbmlpkgspec\logos\sbml-badge.jpg"
  File "dist\sbmlpkgspec\logos\sbml-badge.pdf"
  SetOutPath "$INSTDIR\sbmlpkgspec"
  File "dist\sbmlpkgspec\NEWS.txt"
  File "dist\sbmlpkgspec\README.txt"
  File "dist\sbmlpkgspec\sbmlpkgspec-doc.pdf"
  File "dist\sbmlpkgspec\sbmlpkgspec-doc.tex"
  File "dist\sbmlpkgspec\sbmlpkgspec.bib"
  File "dist\sbmlpkgspec\sbmlpkgspec.cls"
  File "dist\sbmlpkgspec\VERSION.txt"

SectionEnd

Section un.sbmlpkgspec
  Delete "$INSTDIR\sbmlpkgspec\VERSION.txt"
  Delete "$INSTDIR\sbmlpkgspec\sbmlpkgspec.cls"
  Delete "$INSTDIR\sbmlpkgspec\sbmlpkgspec.bib"
  Delete "$INSTDIR\sbmlpkgspec\sbmlpkgspec-doc.tex"
  Delete "$INSTDIR\sbmlpkgspec\sbmlpkgspec-doc.pdf"
  Delete "$INSTDIR\sbmlpkgspec\README.txt"
  Delete "$INSTDIR\sbmlpkgspec\NEWS.txt"
  Delete "$INSTDIR\sbmlpkgspec\logos\sbml-badge.pdf"
  Delete "$INSTDIR\sbmlpkgspec\logos\sbml-badge.jpg"
  Delete "$INSTDIR\sbmlpkgspec\logos\sbml-badge.eps"
  Delete "$INSTDIR\sbmlpkgspec\LICENSE.txt"
  Delete "$INSTDIR\sbmlpkgspec\LICENSE.html"
  Delete "$INSTDIR\sbmlpkgspec\COPYING.txt"
  Delete "$INSTDIR\sbmlpkgspec\COPYING.html"
  Delete "$INSTDIR\sbmlpkgspec\AUTHORS.txt"
  Delete "$INSTDIR\sbmlpkgspec\.svnignore"
  RMDir "$INSTDIR\sbmlpkgspec\logos"
  RMDir "$INSTDIR\sbmlpkgspec"
SectionEnd
