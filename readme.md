                                        # charPlayer
                                        
                                        
          命令行字符动画,c++版本初试。
    使用说明：利用ffmpeg软件截图视频。
    找到ffmpeg.exe所在文件：
    -r 指帧率 image2后面指截图生成路径.%4d为命名方式。
            ffmpeg –i 文件所在路径 –r 10 –f image2 C:/Users/Administrator/Desktop/backup/picture/%4d.jpeg 
            
            运行时调整cmd窗口大小(右键cmd 字体大小选3*5 布局宽度368，高度200)
            
            存在闪烁问题,待更新双缓冲区。(已解决,文中利用WriteConsoleOutputCharacterA解决了闪烁问题便没深入双缓冲区问题.)
           
          
          
    运行截图：
           ![Image text](https://github.com/xxx-032/charPlayer/raw/master/main/show.PNG)
          
          
    参考教程：http://tieba.baidu.com/p/2850192041
    双缓冲区教程:https://blog.csdn.net/weixinhum/article/details/72179593
