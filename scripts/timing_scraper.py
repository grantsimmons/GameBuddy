from bs4 import BeautifulSoup as soup
from urllib.request import urlopen as uReq
my_url = 'https://pastraiser.com/cpu/gameboy/gameboy_opcodes.html'
uClient = uReq(my_url)
page_soup = soup(uClient.read(), "html.parser")
uClient.close()
tables = page_soup.findAll("table")
filename = "timings.csv"
f = open(filename, "w")

for x in range(2):
    counter = 0
    table = []

    while counter < 3:
        if counter < 2:
            table = tables[0]
        else:
            table = tables[1]
        rows = table.findAll("tr")
        for r_index, row in enumerate(rows):
            if r_index != 0:
                columns = row.findAll("td")
                for col_index, column in enumerate(columns):
                    if col_index != 0:
                        breaks = column.findAll("br")
                        if len(breaks) == 0:
                            f.write('0,')
                        for br_index, br in enumerate(breaks):
                            if br_index == 0:
                                num_cycles = str(br.nextSibling[1:])
                                if '/' in num_cycles:
                                    #print(num_cycles.index('/'))
                                    if counter == 1: #Unbranched
                                        if x == 0:
                                            f.write(str(int(int(num_cycles[num_cycles.index('/') + 1:]) / 4)) + ',')
                                        else:
                                            f.write(str(int(int(num_cycles[num_cycles.index('/') + 1:]))) + ',')
                                    else: #Unbranched
                                        if x == 0:
                                            f.write(str(int(int(num_cycles[:num_cycles.index('/')]) / 4)) + ',')
                                        else:
                                            f.write(str(int(int(num_cycles[:num_cycles.index('/')]))) + ',')
                                else:
                                    if x == 0:
                                        f.write(str(int(int(br.nextSibling[1:]) / 4)) + ',')
                                    else:
                                        f.write(str(int(int(br.nextSibling[1:]))) + ',')
                f.write('\n')
        f.write('\n')
        counter += 1

f.close()
