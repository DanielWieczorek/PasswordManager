PasswordManager
===============

This is my personal password manager. I build myself to learn some C and to have a piece of software to manage my passwords I trust. C seems the perfect language for that as I manage the memory myself.

The current plan is to go with a very simplistic aproach. Generate a password, encrypt it with a master password and store it in a sqlite db. Later on type in master password, type in website and get username and password.

The database will probably contain only one table with the following fields:
1. username -  encrypted
2. entity - probably a hash sha512 or something equally strong. Maybe even encrypted. 
3. The password - encrypted

The actual name of the entity at which the authentication is done (website or computer) is only interesting for getting the right data set. This is the input for the search so we should already know it because we just typed it in. It also might have a security benefit that even if the encryption is broken somehow the site cannot be retrieved. 

I am not sure about the encryption algorithm yet. The two candidates considered are AES 256 bit and Twofish 256. 

The design goals for this program are as follows:
1. keep it simple. With complexity there will come errors and security issues.
2. Delete passwords from memory as soon as possible.
3. Protect the passwords that are stored as good as possible.
4. Dont leave passwords in any log file. Not sure what the bash logs 

