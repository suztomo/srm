#!/usr/bin/env python
# -*- coding: utf-8 -*-
import re
import time
import getpass
# http://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm414
import mechanize



method = "http://"
host = "www.topcoder.com"
domainURL = method + host
firstNumber = 214
lastNumber = 415

getBodyRegex = re.compile(r'<!-- BEGIN BODY -->(?P<body>.*)<!-- END BODY -->', re.DOTALL)

getProblemRegex = re.compile(r'<a href="(?P<url>/stat\?c=problem_statement[^"]+)"[^\>]*>(?P<title>[^<]+)</a>.*?Used as: (?P<used>[^<]+):',
                             re.IGNORECASE | re.DOTALL)
ampRegex = re.compile(r'&amp;')

removeBGColorRegex = re.compile(r'BGCOLOR\S+')
removeIMGRegex = re.compile(r'<IMG[^>]+>', re.IGNORECASE)

problemDirectory = "problems"
ds = "/"
srms = {}

summary_location_fmt = "/tc?module=Static&d1=match_editorials&d2=srm%d"


if __name__ == "__main__":
    br = mechanize.Browser()

    try:
        br.open("http://www.topcoder.com/tc?&module=Login")
        br.select_form(name="frmLogin")
        br["username"] = raw_input('username: ')
        br["password"] = getpass.getpass('password for %s: ' % br['username'])
        br.submit()
    except:
        print("Could not access login form")
        exit(1)

    print("Starts to download...")
    for i in range(firstNumber, lastNumber):
        problemURL = domainURL + summary_location_fmt % i
        try:
            res = br.open(problemURL)
        except :
            print("Fail to open SRM%d" % i)
            continue

        html = res.read()
        summary_html = open(problemDirectory + ds + str(i) +".html", "w")
        summary_html.write(html)
        summary_html.close()
        problemCount = 0
        for m in getProblemRegex.findall(html):
            try:
                res = br.open(domainURL + ampRegex.sub('&', m[0]))
            except :
                print("Fail to open %s" % (domainURL + ampRegex.sub('&', m[0])))
            html = res.read()
            if html.find('name="frmLogin"') >= 0:
                print("Authentication failed")
                exit(1)
            f = open(problemDirectory + ds + str(i) + "-" + str(problemCount+1) + ".html", "w")
            f.write(html)
            f.close()
            problemCount += 1
            time.sleep(1)
        if (problemCount == 0):
            print("Can't find the proglems in SRM%d." % i)
        else:
            print("SRM %d has %d problems." % (i, problemCount))
