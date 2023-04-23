import requests

r = requests.get('https://in.bookmyshow.com/national-capital-region-ncr/movies/avengers-endgame/ET00090482')
text = r.text
if(text.find('Book Tickets') != -1):
    print('yes')
    from twilio.rest import Client

    # Your Account Sid and Auth Token from twilio.com/console
    # DANGER! This is insecure. See http://twil.io/secure
    account_sid = 'x'
    auth_token = 'x'
    client = Client(account_sid, auth_token)

    message = client.messages \
                    .create(
                        body="ENDGAME TICKETS OUT HHZ",
                        from_='+x',
                        to='+x'
                    )

    print(message.sid)
else:
    print ('no')
    
