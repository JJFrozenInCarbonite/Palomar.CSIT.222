

countries = []
with open('countries.csv', 'r', encoding='utf-8') as file:
    for line in file.readlines():
        countries.append(line.split(',')[3].strip().replace('"', ''))
countries = countries[1:]

for i,country in enumerate(countries):
    if country in (
        'Beliz',
        'Cambodge',
        'Mexique',
        'Mozambique',
        'Zaïre',
        'Zimbabwe'):
        countries[i] = "le " + country
    elif country[-1] == 's':
        countries[i] = 'les ' + country
    elif 'AÉEÎIOUY'.find(country[0]) != -1:
        countries[i] = "l'" + country
    else:
        countries[i] = 'les ' + country
    
print("Result:")
for country in countries:
    print(country)