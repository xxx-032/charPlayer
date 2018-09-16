                                        # charPlayer
                                        
                                        
          命令行字符动画,c++版本初试。
    使用说明：利用ffmpeg软件截图视频。
    找到ffmpeg.exe所在文件：
    -r 指帧率 image2后面指截图生成路径.%4d为命名方式 -s指图片大小。
            ffmpeg -i BadApple.mp4 -s 200*200 -r 25  -f image2 C:/Users/Administrator/Desktop/backup/picture/%4d.jpg
            运行时调整cmd窗口大小(右键cmd 字体大小选3*5 布局宽度200，高度200)
            
            存在闪烁问题,待更新双缓冲区。(已解决,文中利用WriteConsoleOutputCharacterA解决了闪烁问题便没深入双缓冲区问题.)(已完成双缓冲区创建)
           
          
          
    运行截图：
           ![Image text](https://raw.githubusercontent.com/xxx-032/charPlayer/master/main/show.PNG)
          
          
          目标：声频图片实时转换做成播放器！赶紧的
          (暂时放弃,超出能力范围嘤嘤嘤...)
          
    参考教程：http://tieba.baidu.com/p/2850192041
    双缓冲区教程:https://blog.csdn.net/weixinhum/article/details/72179593
    
    输出音频：
     ffmpeg -i .[迅雷下载xunbo.cc]爱情公寓第二季EP20.rmvb -f wav -ar 16000 2-20.wav
       参数说明
    -i .[迅雷下载xunbo.cc]爱情公寓第二季EP20.rmvb // 输入的文件路径
    -f wav ///输出wav格式的文件
     -ar 16000 //采样率为16K
     2-20.wav // 输出的文件名
  
    
