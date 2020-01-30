<pre>
   __                 __    __                     
  /__\_ _ ___ _   _  / / /\ \ \___  _ __ _ __ ___  
 /_\/ _` / __| | | | \ \/  \/ / _ \| '__| '_ ` _ \ 
//_| (_| \__ \ |_| |  \  /\  / (_) | |  | | | | | |
\__/\__,_|___/\__, |   \/  \/ \___/|_|  |_| |_| |_|
              |___/                                
</pre>
# EasyWorm: the simple SSH worm
An simple Internet SSH worm implementation for educational purposes.
By using a simple user password database this worm tries to connect 
throught SSH servers and propagate the code by copying and executing
the worm on the remote machine.

Each time EasyWorm has a success access to an SSH server it will notify
the IP address, user and password to an IRC server.
