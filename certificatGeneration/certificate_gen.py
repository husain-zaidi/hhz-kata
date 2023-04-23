#generate certificates by going thorugh an excel sheet

import openpyxl, os
from PIL import Image, ImageDraw,ImageFont
import smtplib

from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

wb = openpyxl.load_workbook('sheet.xlsx')
sheet = wb['Form responses 1']
smtpObj = smtplib.SMTP("smtp.gmail.com", 587)
smtpObj.ehlo()
smtpObj.starttls()
smtpObj.login('husainhz7@gmail.com','husain026845')



#make the participation cert
def make_cert(templatePath:str, name:str):
    template = Image.open(templatePath)
    draw = ImageDraw.Draw(template)
    fontsFolder = "/media/husainhz7/Local Disk/Windows/Fonts"
    sourceSansFont = ImageFont.truetype(os.path.join(fontsFolder,'SourceSansPro-Regular.otf'),22)
    text_width, text_height = draw.textsize(name,font=sourceSansFont)
    max_width = 322
    draw.text((398+(max_width-text_width)/2,449),name,fill='black',font=sourceSansFont)
    template.save(f'gen/{name}.png')
    return

#send email
def send_mail(mail:str, members, team:str):
    msg = MIMEMultipart()
    msg['Subject'] = f'HackAMU 2 certificates for Team {team}'
    msg['From'] = "husainhz7@gmail.com"
    msg['To'] = mail
    print(f'sending to {mail}')
    for member in members:
        fp = open(f'gen/{member}.png','rb')
        img = MIMEImage(fp.read())
        fp.close()
        print(f'attatching {member}.png')
        msg.attach(img)
    smtpObj.sendmail('husainhz7@gmail.com',mail,msg.as_string())
    print('sent mail to ' + mail)
    return
#sheet.max_row + 1
for row in range(2, 3):
    mail = sheet['B'+str(row)].value
    name = sheet['C'+str(row)].value
    members = []
    members.append(sheet['F'+str(row)].value)
    members.append(sheet['I'+str(row)].value)
    members.append(sheet['L'+str(row)].value)

    print(f'Team: {name} ')

    for member in members:
        if(member != None):
            make_cert("part_small.png",member)
    
    send_mail(mail,members, name)
            
smtpObj.quit()
print("Done!")
    


