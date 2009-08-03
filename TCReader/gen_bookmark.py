#!/usr/bin/env python
# -*- coding: utf-8 -*-
import re
from dircache import listdir
import base64
import string
from download_problems import problemDirectory
from download_problems import ds, summary_location_fmt, domainURL
from download_problems import ampRegex


getBodyRegex = re.compile(r'<!-- BEGIN BODY -->(?P<body>.*)<!-- END BODY -->', re.DOTALL)
removeBGColorRegex = re.compile(r'BGCOLOR\S+')
removeIMGRegex = re.compile(r'<IMG[^>]+>', re.IGNORECASE)
removeWidthValue = re.compile(r'COLSPAN="7"')
getProblemRegex = re.compile(r'<a href="(?P<url>/stat\?c=problem_statement[^"]+)"[^\>]*>(?P<title>[^<]+)</a>.*?Used as: (?P<used>[^<]+):',
                             re.IGNORECASE | re.DOTALL)
removeUnusedTable1 = re.compile('<TABLE.+?</TABLE>', re.DOTALL)
removeUnusedTR = re.compile('<TR.+?Problem Statement for.+?</TR>',
                            re.IGNORECASE | re.DOTALL)
pageTemplate = string.Template("""<html>
<head>
<title>$title</title>

<style>
body {
width: 480px;
}



</style>
</head>

<body>
<h1>$title</h1>
<p>SRM$srm $used</p>
$body

<h2>Analysis</h2>
<p><a href="$analysis">Problem sets and Analysis</a></p>
</body>
</html>

""")


bookmarkTemplate = string.Template("""
<!DOCTYPE NETSCAPE-Bookmark-file-1>
	<HTML>
	<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=UTF-8">
	<Title>TopCoder Single Round Matches</Title>
	<H1>Bookmarks</H1>
	<DT><H3 FOLDED>Single Round Matches</H3>
	<DL><p>
$entries
        </DL><p>
</HTML>
""")


entries = ""

directoryEntry100 = string.Template("""
             <DT><H3 FOLDED>$name</H3>
             <DL><p>
""")

directoryEntryEnd100 = """
             </DL><p>
"""

directoryEntry10 = string.Template("""
                    <DT><H3 FOLDED>$name</H3>
                    <DL><p>
""")

directoryEntryEnd10 = """
                    </DL><p>
"""

entryTemplate = string.Template("""
       	                   <DT><A HREF="data:text/html;charset=EUC-JP;base64,$encodedBody">$title</A>
""")

directoryPrefix100 = "SRM"
directoryPrefix10 = "srm"
import pdb

if __name__ == "__main__":

    file_names = listdir(problemDirectory + ds)
    srm_dict = {}
    srms = []
    count = 1

    for name in file_names:


        srm = name[:3]
        if not srm in srm_dict:
            srm_dict[srm] = 1
        else:
            if name[4:5] != "h":
                srm_dict[srm] = int(name[4:5])
            else:
                srms.append((int(srm), srm_dict[srm]))
    firstNumber = srms[0][0]
    entries = directoryEntry100.substitute(
        name = (directoryPrefix100 + str(firstNumber) + "-"))
    entries += directoryEntry10.substitute(
        name = (directoryPrefix10 + str(firstNumber) + "-"))

    for i, problem_num in srms:

        count += 1
#        if count > 10:
#            break

        if (i % 100 == 0 and i != firstNumber):
            entries += directoryEntryEnd10
            entries += directoryEntryEnd100
            entries += directoryEntry100.substitute(
                name = (directoryPrefix100 + str(i) + "-"))
        if (i % 10  == 0 and i != firstNumber):
            if (i % 100 != 0):
                entries += directoryEntryEnd10
            entries += directoryEntry10.substitute(
                name = (directoryPrefix10 + str(i) + "-"))
        problemURL = domainURL + summary_location_fmt % i

        summary_fname = problemDirectory + ds + str(i) + ".html"
        summary_f = open(summary_fname, "r")
        summary_html = summary_f.read()
        summary_f.close()
        for jj, m in enumerate(getProblemRegex.findall(summary_html)):
            j = jj + 1
            f_name = problemDirectory + ds + str(i) + "-" + str(j) + ".html"
            f = open(f_name)
            html = f.read()
            f.close()
            body = getBodyRegex.search(html).group("body")
            body = removeBGColorRegex.sub('', body)
            body = removeIMGRegex.sub('', body)
            body = removeWidthValue.sub('', body)
            body = removeUnusedTable1.sub('',body, 1)
            body = removeUnusedTR.sub('', body, 1)
            dic = {}
            dic['srm'] = i
            dic['url'] = domainURL + ampRegex.sub('&', m[0])
            dic['title'] = m[1]
            dic['used'] = m[2]
            dic['body'] = body
            dic['analysis'] = problemURL
            dic['html'] = pageTemplate.substitute(dic)
            title = "%d-%d %s" % (i, j,dic['title'])
            entries += entryTemplate.substitute(
                encodedBody = (base64.b64encode(dic['html'])), title=title
                )
        print("SRM%d" % i)
    entries += directoryEntryEnd10
    entries += directoryEntryEnd100
    bookmarks = open("bookmarks.html", "w")
    bookmarks.write(bookmarkTemplate.substitute(entries = entries))
    bookmarks.close()
