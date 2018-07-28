                                        # charPlayer
                                        
                                        
          命令行字符动画,c++版本初试。
    使用说明：利用ffmpeg软件截图视频。
    找到ffmpeg.exe所在文件：
    -r 指帧率 image2后面指截图生成路径.%4d为命名方式。
            ffmpeg –i 文件所在路径 –r 10 –f image2 C:/Users/Administrator/Desktop/backup/picture/%4d.jpeg 
            
            存在闪烁问题,待更新双缓冲区。
          
          
    运行截图：
           ![Image text](https://github.com/xxx-032/charPlayer/raw/master/main/show.PNG)
          
          
    参考教程：http://tieba.baidu.com/p/2850192041
