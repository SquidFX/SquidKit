import requests

url = 'http://localhost:8000/example.xml'
response = requests.get(url)

if response.status_code == 200:
    xml_content = response.content.decode('utf-8')
    print('XML file contents:')
    print(xml_content)
else:
    print('Failed to retrieve XML file.')

