# YTDes
Desktop Youtube browser made with QtWebEngine. Store subscriptions/channels locally without an account. 

## Install

    git clone https://github.com/uwuzi/YTDes/  
    cd YTDes  
    mkdir build && cd build  
    qmake -makefile ../ytd.pro  
    make  
    
## Subscriptions  
Program will read "subscriptions" from a file at /home/*username*/.config/ytdes/ytdconf  
The layout of the file is just:  

    "Channel Nickname 1"  
    <URL-to-channel-1>  
    "Channel Nickname 2"  
    <URL-to-channel-2>  
    
    "Channel Nickname 3"  
    <URL-to-channel-3>  
    
