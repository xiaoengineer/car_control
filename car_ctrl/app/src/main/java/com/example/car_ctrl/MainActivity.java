package com.example.car_ctrl;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import java.io.OutputStream;
import java.io.IOException;
import android.view.MotionEvent;
//import com.gcssloop.widget.RockerView;

public class MainActivity extends AppCompatActivity {
    Button button;
    Button button4;
    Button button5;
    Button button6;
    Button button7;
    Button button8;
    Button button9;
    Button button2;
    Button button3;
    ImageButton imageButton;
    ImageButton imageButton1;
    private OutputStream outputStream;
    public int speed = 250;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
       //   RockerView rocker = (RockerView)findViewById(R.id.rocker);
        button = (Button)findViewById(R.id.button);
        button2 = (Button)findViewById(R.id.button2) ;
        button3 = (Button)findViewById(R.id.button3);
        button4 = (Button)findViewById(R.id.button4);
        button5 =(Button)findViewById(R.id.button5);
        button6 = (Button)findViewById(R.id.button6);
        button8 = (Button)findViewById(R.id.button8);
        button7 = (Button)findViewById(R.id.button7);
        button9 = (Button)findViewById(R.id.button9);
        imageButton1 = (ImageButton) findViewById(R.id.imagebutton1);
        imageButton = (ImageButton)findViewById(R.id.imagebutton);
        final TextView text = (TextView)findViewById(R.id.textView2);
        text.setText("显示");

        imageButton.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        outputStream = bluethooth.outputStream;
                        try {
                            outputStream.write(0x00); //方向
                        } catch (IOException e) {
                            // TODO Auto-generated catch block
                            e.printStackTrace();
                        }
                        break;
                    case MotionEvent.ACTION_UP:
                        break;
                        default:break;
                }
                return false;
            }
        });
        imageButton1.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                switch (event.getAction()){
                    case MotionEvent.ACTION_DOWN:
                        outputStream = bluethooth.outputStream;
                        try {
                            outputStream.write(0x01); //方向
                        } catch (IOException e) {
                            // TODO Auto-generated catch block
                            e.printStackTrace();
                        }
                    case MotionEvent.ACTION_UP:
                        break;
                        default:break;
                }
                return false;
            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x02); //前进控制
                    speed = speed +20;
                    text.setText("速度：" + speed);
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });

        button8.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x03); //后退控制
                    if(speed < 250){
                        speed = 250;
                    }else {
                        speed = speed - 20;
                    }
                    text.setText("速度"+ speed);

                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        button6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x04); //停止
                    speed = 250;
                    text.setText("速度"+ speed);
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        button4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x06); //灯
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        button5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x05); //蜂鸣器
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });

        button2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x07); //左转向
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });

        button3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x08); //右转向
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });

        button7.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x09); //前进
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });

        button9.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                outputStream = bluethooth.outputStream;
                try {
                    outputStream.write(0x0A); //后退
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        /*if(null != rocker){
            rocker.setListener(new RockerView.RockerListener() {
                @Override
                public void callback(int eventType, int currentAngle, float currentDistance) {
                    switch (eventType){
                        case RockerView.EVENT_ACTION:
                            outputStream = bluethooth.outputStream;
                            angle = currentAngle;
                            distance = (int)currentDistance;
                            text.setText("角度"+cmdMange(1, angle, distance));
                            //cmdMange(1, angle, distance);
                            try {
                                outputStream.write(cmdMange(1, angle, distance));

                            } catch (IOException e) {
                                // TODO Auto-generated catch block
                                e.printStackTrace();

                            }
                            break;
                        case RockerView.EVENT_CLOCK:

                            break;
                    }
                }
            });
        }*/
    }

}
