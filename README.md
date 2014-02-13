What this is:  It is a control plane for the arduino.  While the arduino runs normally and executes code, this can interperet commands from a serial connection.  Combined with a little love power from the raspberry pi, this thing is very powerful.  While keeping a background serial connection (this disables the DTR reset) in a tty1 or other non virtual console, you can interface your arduino with ease of use right over usb.  This is awesome because with hubs you can have ridiculous amounts of arduinos controlled by the same pi.  The pi does all the heavy thinking while the arduinos loop through their commands. Then the pi's all bam, This is what I want you to do.  I unno. I mainly made this for easier debugging of new hardware.  It should have lot's potential uses in final product hacking stuffs though.

How to use, upload to device. type (enter) in a serial terminal and see what can pop up.  Each command has a number. I haven't made a process to parse string input so it's just the numbers for now. Each word is spacebar delimited. an input of: 2 1 1 (enter) :reads digital pin 1. It returns whether pin 1 is high or low. While : 2 2 1 (enter) : will return the value of analog pin 1.

Todos:

Get RTC shield.

Set up gpio pins for serial transmission. Though right now I'm feeling it can go blow itself.

!important! Get gf... round 2...

Set up servo shield

Arduino -> lego mindstorms? stupid funding.

Set up tab completion.

In fact, get word interperatation period.

Refine my blantant waste of data.

Set syntax error to a variable.

crunch bools into combined integers.

Love science.



Note: This is all done from a raspberry pi and Ino on a mega2560. Testing with an uno soon.
