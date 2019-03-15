# pyrforosTelemetry18
Code for arduino-piccolo communication protocol, digital implemetation of motor measuring system.
During Shell Eco Marathon 2018 our vehicle was equipped with circuitry that measured polar voltage and current of our motor's phases.
The system included two processors, a Texas Instruments Piccolo  TMS320f28027f and an arduino.
The Piccolo processor calculated RMS Current and the motor's power sending them to the arduino via Serial Communication.
The arduino was responsible for safely managing the incoming data, and storing them to an sd card together with GPS information.
Finaly it displayed the value of the RMS Current on an lcd screen for the driver.
All this data (Power,Current,Location) was then processed by a Matlab script performing round segmentation and mapping the values on
the track's model. We were then able to evaluate the drivers performace and adap our driving behaviour on the track. 

<iframe src='https://view.officeapps.live.com/op/embed.aspx?src=[https://github.com/Markos-NTUA/pyrforosTelemetry18/blob/master/Markos_Presentation.pptx]' width='100%' height='600px' frameborder='0'>
