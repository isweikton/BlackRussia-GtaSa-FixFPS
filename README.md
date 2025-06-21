
# BlackRussia-GtaSa-FixFPS
Fix FrameRate limit for BR based on GTA:SA 1.08



## Screenshoot

![wn](https://avatars.mds.yandex.net/i?id=bf1fcfda41474b0ed20a96b60d5028e39de92320-8931611-images-thumbs&ref=rim&n=33&w=320&h=200)


## Features

- Support all Black Russia version's
- Low memory usage
- Easy to install


## Usage/Examples
###### Note: load the plugin after libsamp.so init
```smali
const-string v0, "wnframerate"
invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
```
or
```java
System.loadLibrary("wnframerate");
```

