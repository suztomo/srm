#!/usr/bin/env python3.0
# -*- encode:utf-8 -*-

import sys

t = [" <-- この行は削除されました","<-- この行は追加されました"]
i = 0
for l in sys.stdin:
    for s in l.split("\\n"):
        print(s + t[i])
    i += 1
