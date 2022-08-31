import re
text=''
file = open('poem.txt', encoding='gb18030', errors='ignore')
for line in file:
    text=text+line
file.close()
result=re.findall(' *[Aa][a-z][a-z] ',text)
result=set(result)
print(result)