# FrogAuth
An authentication system made to be secure without relying on encription or other mehthods to conceal the data being sent - requires access to both the host and client, so use cases are limited.

# Warning - I am stupid, there are almost certaintly issues with this, please dont use it with anything important.

There currently isnt a way to connect to the script from remotly, i'm probably going to make that soon (not sure if it'll be before or after i upload my project to high seas we'll see). 

To use this script on linux, run `gcc password.c -o FrogAuth` in your terminal, make a file named `passlist.txt`, input your password list in passlist.txt (example provided in the repo, max size is 64 characters and 36 passwords, though this is largely arbitrary), then run `./FrogAuth`. The script will give the first letter of the password it selected, then you can input the matching password. This is currently just a POC, though I do plan to make it more useful.

# FAQ:

Why should you use this? You shouldn't, but i made it so that I didnt have to worry about messing with encrypting the passwords for when you send it over or while it's stored on the host (assuming the host is secure as well). It makes it so that if an attacker steals a password you send to the server, they wont be able to use that password to login to the server as the password you sent over will be removed from the candidate list.

What are the problems with this aproach? The main problems come up from the user having to memorize many passwords, meaning they cant be very secure, and the factor of the passwords being unencrypted meaning that if an attacker got access to the password list, yknow. The script does have protection against brute force, but if the attacker intercepted the password, they might be able to access to server anyways, but I dont know enough about networking to be sure.


