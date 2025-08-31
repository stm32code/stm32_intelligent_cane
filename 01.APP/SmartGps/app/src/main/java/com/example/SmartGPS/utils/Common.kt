package com.example.SmartGPS.utils


import com.itfitness.mqttlibrary.MQTTHelper

object Common {
    var Sever =
        "tcp://iot-06z00axdhgfk24n.mqtt.iothub.aliyuncs.com:1883" //mqtt连接ip oneNET为183.230.40.39

//                var Sever = "tcp://192.168.63.225:1883" //mqtt连接ip oneNET为183.230.40.39
    var PORT = "6002"//oneNET为6002
    var ReceiveTopic = "/broadcast/h9sjRktamj8/test2"
    var PushTopic = "/broadcast/h9sjRktamj8/test1"
    var DriveID =
        "h9sjRktamj8.smartapp|securemode=2,signmethod=hmacsha256,timestamp=1714195808122|"  //mqtt连接id  oneNET为设备id
    var DriveName = "smartapp&h9sjRktamj8"  //设置用户名。跟Client ID不同。用户名可以看做权限等级"  oneNET为产品ID
    var DrivePassword =
        "7c0da8535713d9af76aefa04363c2231990bf4de58bc13d0589c430d13a2f09a"// //设置登录密码  oneNET为设备鉴权或apikey
    var Drive2ID = "**"
    var api_key = "***=wcjTY="
    var DeviceOnline = false //底层是否在线
    var LatestOnlineDate = "离线" //最近在线时间
    var mqttHelper: MQTTHelper? = null
}


