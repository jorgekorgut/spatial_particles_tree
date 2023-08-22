# Spatial particles tree  
## To compile  
``` make in the root folder ```  

## To launch  
``` ./build/main ```  
Make sure that you have the rights to execute the file.  


## Install graphical library
```apt-key adv --fetch-keys https://repos.codelite.org/CodeLite.asc```  
```sudo apt-add-repository 'deb https://repos.codelite.org/wx3.2.0/ubuntu/ jammy universe'```  
```sudo apt-get update```  
```apt-get install libwxbase3.2-0-unofficial \
                libwxbase3.2unofficial-dev \
                libwxgtk3.2-0-unofficial \
                libwxgtk3.2unofficial-dev \
                wx3.2-headers \
                wx-common \
                libwxgtk-media3.2-0-unofficial \
                libwxgtk-media3.2unofficial-dev \
                libwxgtk-webview3.2-0-unofficial \ 
                libwxgtk-webview3.2unofficial-dev \ 
                libwxgtk-webview3.2-0-unofficial-dbg \ 
                libwxbase3.2-0-unofficial-dbg \
                libwxgtk3.2-0-unofficial-dbg \
                libwxgtk-media3.2-0-unofficial-dbg \
                wx3.2-i18n \
                wx3.2-examples```  

LDFLAGS=$(pkg-config --libs gtk+-3.0) CXXFLAGS=$(pkg-config --cflags gtk+-3.0) make -j$(nproc)
