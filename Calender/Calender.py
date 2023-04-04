from datetime import datetime


def calender(inputs0, inputs0b, inputs1, inputs1b):
    guy0 = []
    guy0b = [datetime.strptime(inputs0b[0], '%H:%M'), datetime.strptime(inputs0b[1], '%H:%M')]
    guy1 = []
    guy1b = [datetime.strptime(inputs1b[0], '%H:%M'), datetime.strptime(inputs1b[1], '%H:%M')]

    for s in inputs0:
        guy0.append([datetime.strptime(s[0], '%H:%M'), datetime.strptime(s[1], '%H:%M')])

    for s in inputs1:
        guy1.append([datetime.strptime(s[0], '%H:%M'), datetime.strptime(s[1], '%H:%M')])


    def getfree(guy, guyb):
        free = []

        if guyb[0] != guy[0][0]:
            free.append([guyb[0], guy[0][0]])

        for index, span in enumerate(guy):
            if index + 1 < len(guy):
                if span[1] != guy[index + 1][0]:
                    free.append([span[1], guy[index + 1][0]])

        if guy[-1][1] != guyb[1]:
            free.append([guy[-1][1], guyb[1]])

        return free

    free0 = getfree(guy0, guy0b)
    free1 = getfree(guy1, guy1b)

    matches = []

    for a in free0:
        for b in free1:
            if b[0] > a[1]:
                break

            if b[1] > a[0]:
                matches.append([max(a[0], b[0]), min(a[1], b[1])])


    results = []
    for t in matches:
        results.append([t[0].strftime("%H:%M"), t[1].strftime("%H:%M")])

    return results

inputs0 = [
    ['9:00', '10:30'],
    ['12:00', '13:00'],
    ['16:00', '18:00']]
inputs0b = ['9:00', '20:00']

inputs1 = [
    ['10:00', '11:30'], 
    ['12:30', '14:30'], 
    ['14:30', '15:00'], 
    ['16:00', '17:00']]
inputs1b = ['10:00', '18:30']

print(calender(inputs0, inputs0b, inputs1, inputs1b)) # Time: 2h 40min