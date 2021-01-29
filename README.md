# 高三 Arduino 專題

> 生活科技課看到這個 Arduino 名字好像很潮就選了，也沒什麼特殊想法。
> 上網研究一下以後發現，原來是 maker 相關的東西，就像是一個小心臟，組織、控制各組件的運作來達成目的，操作邏輯簡單，使用 C-like 語言
> 最後決定做四軸機，三個傻瓜裡面會飛的那台

## 材料

- Arduino
    - 網購、學校提供
    - 作為主控制器
- 各種模塊
    - GPS / WIFI / 陀螺儀
    - 網購
- 電子變速器（電變）
    - 網購
    - 控制四顆無刷馬達
        - input: power, 4xPWM
        - output: 4x 三相交流電
- 無刷馬達x4、螺旋槳
    - 網購
    - 要注意槳規格尺寸、馬力、電變、電池的搭配
    - 正反槳至少各買兩組，一定會摔壞的，買越多越好反正很便宜
- 電池
    - 網購
    - 注意不要太重
- 木頭
    - 學校提供
- 保麗龍、電火布
    - 整體防撞要到位，測試的時候才不會馬上下課。

## 工具

- 焊接工具
    - 網購的各種零件通常需要自己焊接插頭、插座
- 木工工具
    - 四個軸使用飛機木製造
    - 線鋸機、輪鋸機、帶鋸機
        - 切出理想外觀
    - 刨木機
        - 修至精準尺寸
    - 電鑽、砂紙
        - 細節加工
- 3D 列印機
    - 四軸機本體平台、小零件可以自行列印出來用
- 雷射切割機
    - 切木料或是裝飾

## 圖文分享

### 開箱

- 用集運過來就是這樣一坨
    ![](https://i.imgur.com/aTN5LrI.jpg)
- 可以多重遞迴開箱
    ![](https://i.imgur.com/zpmOkW9.jpg)
- 所有店家的保護都很齊全
    ![](https://i.imgur.com/eAhNp2g.jpg)
- 大部分模塊本體其實很小
    ![](https://i.imgur.com/6ZytEXm.png)
- 淘寶來的飛行核心保護的挺好，無受損，最後收完大概只有這樣
    ![](https://i.imgur.com/3ziulyN.jpg)

### 硬體

- 反正都先串起來玩玩看
    ![](https://i.imgur.com/ZWPIjvu.jpg)
- 馬達，左上是起始，中上、右上開始拆封，下方是預備要把插頭焊接，鉗子配上橡皮筋，沒有固定座也能單人完成。
    ![](https://i.imgur.com/ThrxlwD.jpg)
- 像這樣夾著，可以先補滿焊錫，再插電線，注意速度不要加熱太久，線跟頭都會壞掉
    ![](https://i.imgur.com/o34Oa2y.jpg)
- 旁邊有個小洞，電烙鐵很好擺，先速速填銲錫，之後拿錫線換銅線就接好了
    ![](https://i.imgur.com/OBTcbpD.png)
- 焊接完成像這樣，小時候不會對焦抱歉
    ![](https://i.imgur.com/ttXJXOe.jpg)
- 接著要用熱縮套收口
    ![](https://i.imgur.com/vQ4SiVt.jpg)
- 加工完畢以後鎖上底盤，底盤鎖在木板上像這樣，記得先鎖穩才測試馬達
    ![](https://i.imgur.com/6Y09OCJ.png)
- 這是我用的型號
    ![](https://i.imgur.com/E7PZDrV.jpg)
- 驅動馬達需要比較大電流，arduino 撐不住的，必須用電變，arduino 負責給控制訊號即可，金援夠的話，安培儘量買大不會虧，如果不是太特殊的，買這種四合一可以省空間，也比較好佈線
    ![](https://i.imgur.com/ECJWnIv.jpg)
- 測試各種模組記得要先看懂規格，亂接的下場通常都是燒毀～
    ![](https://i.imgur.com/y40bLnY.jpg)
- 電池想說越大越好結果沒注意到重量，會消耗很多馬力，如果是購買已經焊好插座的形式，記得買對應的插頭回來焊在需要對接的裝置，否則會像我一樣跑去電料行找零件 ... 充電器的部分，也可以順便購買，品質會比較好可以順便監測電池狀態
    ![](https://i.imgur.com/IpfF4Q2.jpg)
- 主體平台我是功能導向設計，上方柱子打 Arduino 孔位，下方可以提供繞線，四邊開孔插木條，好處是摔壞能換，主體用 3d printer 印的～
    ![](https://i.imgur.com/krrCEOI.jpg)
- 一些列印的小零件
    ![](https://i.imgur.com/eQiWLF1.jpg)
- 成品圖
    ![](https://i.imgur.com/jzhJCOS.jpg)

### 軟韌體

> 如果對調變速率(Baud/鮑率)不熟，建議都用他人推薦的或預設即可，省去很多坑，我都用 9600，有時候某些模塊會需要設定，用 `SoftwareSerial` 設定對應腳位的 baud

- 電子變速器
    - 通常用 電變、esc 測試之類的關鍵字，稍微找一下就可以找到測試用的程式碼了
    - 自己修改一下用來測試是否正常，也可以用來參考如何控制電變
    ![](https://i.imgur.com/EymTIrt.png)
- GPS
    - 顯示模塊印出資訊，GPS 買太爛或供電不足會很秀抖，要注意是否是供電不足，因為他還是能運作，只是很坑，Arduino 應該是無法負荷他需要的電力，需要自己從電池拉電。
    ![](https://i.imgur.com/YttRe0t.png)
- 陀螺儀
    - 陀螺儀部分建議買 arduino 出的模塊，不要自己買散裝的便宜貨，因為通訊指令有差，arduino 內建已經寫好一份 ADXL345 的，可以直接用比較方便。
    - 測好之後跟馬達一起實作 PID 演算法，測試時要確認運作是沒有延遲的，也就是一傾斜馬上對應馬達加速。
    - [PID 詳細解說](http://www.inpharmix.com/jps/PID_Controller_For_Lego_Mindstorms_Robots.html)
- wifi
    - 這邊也是建議買官方的模塊，但是官方模塊真的有點大、貴，買野生模塊記得要挑實作好 TCP/UDP、開基地台、連接基地台函式庫的。
    - 這邊也是要注意供電，不夠的話跟 GPS 一樣，會有問題且繼續運作，很難抓錯，供電一定要夠，從電池拉電比較穩。
    - 測試一定要時刻確定保持連線，失聯馬上停馬達（墜機），確認好才上螺旋槳。
    - 上網找範例的關鍵字：socket server client 

## 結語

因為我最終也沒有做出能穩定起飛降落的版本，每次測試都是墜機，加上各種硬體的通訊方式有蠻大差別，所以程式碼還是上網找範例參考較好，我附上的大多是測試程式碼，準備學測就沒繼續胡搞了，僅分享一些心得希望做類似項目的人少踩點坑！


## 網購紀錄

> 很多品項應該失聯了，主要是記錄，以及有一些注意事項


```
老師要的賣家網址:(PS:台灣網拍在服務、價位、與賣家直接對談方面，完全沒競爭力，故選擇淘寶)

集運：
http://shop59449044.taobao.com/shop/view_shop.htm?spm=a1z09.2.9.4.4aVaQz&user_number_id=273972448&v=1
~~~公主集運
集運，服務態度極佳(配台灣黑貓)


ａｒｄｕｉｎｏ：
http://item.taobao.com/item.htm?spm=a1z09.2.9.32.4aVaQz&id=37833297988&_u=q22s4eihd043
~~~Arduino MEGA2560 R3 ??板（2012新版本,ATMEGA16U2,官方版本）
服務態度佳，出貨速度偏慢(需催)


鋰電池＋充電：(需自行焊接)
http://item.taobao.com/item.htm?spm=a1z09.2.9.54.4aVaQz&id=37033373520&_u=q22s4eih80b9
~~~5200MAH/30C T插?技???: ?子11.1V/3S??池
~~~IMAXB6（工厂直?）技???: 套餐一
原廠直銷，服務佳


馬達＋槳：(需自行焊接)
http://item.taobao.com/item.htm?spm=a1z09.2.9.76.4aVaQz&id=21112544886&_u=q22s4eih44b2
~~~白色?机种?: 1??（1正+1反）
~~~?配+香蕉?+??管技???: 2212/1000KV
服務態度佳，ㄠ贈品成功(槳+1對)


陀螺儀：
http://item.taobao.com/item.htm?spm=a1z09.2.9.104.4aVaQz&id=19882412955&_u=q22s4eih953c
新款 ADXL345 IIC /SPI ?字式 ?角?感器 加速度模?
價格極便宜，不建議購買(無技術支援、與arduino開發的ADXL345模組，同晶片不同指令、偏遠地區重慶，貨運較久)


電變（ＥＳＣ）：(需自行焊接)
http://item.taobao.com/item.htm?spm=a1z09.2.9.122.4aVaQz&id=15836442787&_u=q22s4eiha7dc
好盈天行者四合一??技???: 20A
(正版帶雷標)原廠已停產，不建議購買，改選25A較佳


ＷＩＦＩ模組：
http://item.taobao.com/item.htm?spm=a1z09.2.9.138.4aVaQz&id=40901823151&_u=q22s4eih2316
OCROBOT SEED WIFI模? ESP8266 陶瓷天? at指令控制 arduino
與老師的wifi同晶片不同公司，客服為技術人員服務佳，函式庫bug多、使用不同AT指令，不建議購買


ＧＰＳ模組：
http://item.taobao.com/item.htm?spm=a1z09.2.9.154.4aVaQz&id=38609168111&_u=q22s4eih2378
GY-NEO6MV2 ?控GPS模? ?EEPROM MWC APM2.5?控 NEO-6M
ㄠ到贈品(排針)
```

