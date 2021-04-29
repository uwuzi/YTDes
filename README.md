# YTDes
Desktop Youtube browser made with QtWebEngine. Store subscriptions/channels locally without an account. Browse without ads or tracking via invidio.us.  

## Install

    git clone https://github.com/misusi/YTDes/  
    cd YTDes  
    mkdir build && cd build  
    qmake -makefile ../ytd.pro  
    make  
    
## Subscriptions  
Program will read "subscriptions" from a file at /home/*username*/.config/ytdes/ytdconf  
The layout of the file is as follows (empty lines between entries are okay):  

    "Channel Nickname 1"  
    <URL-to-channel-1>  
    "Channel Nickname 2"  
    <URL-to-channel-2>  
    
    "Channel Nickname 3"  
    <URL-to-channel-3>  
    
You can add subscriptions within the program or just edit the text file if you have a bunch.  
    
## More
The literal hamburger icon shows/hides the subscription panel. There is also a little icon at YTdes/assets/ytdes.png that you can use to make a desktop launcher. Really showing off my artistic skills there.  


![Screenshot](screenshot/ytdes.jpg)
