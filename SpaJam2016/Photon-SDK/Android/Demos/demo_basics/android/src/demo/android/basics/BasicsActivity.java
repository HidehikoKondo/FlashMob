package demo.android.basics;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class BasicsActivity extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        mTextView = (TextView)findViewById(R.id.txtView);

        mStopBtn = (Button)findViewById(R.id.buttonStop);
        mStopBtn.setOnClickListener(new OnClickListener()
        {
			public void onClick(View v)
			{
				stopDemo();
			}
		});

        mHandler = new Handler()
        {
        	 public void handleMessage(final Message msg)
             {
                 mTextView.setText((String) msg.obj);
             }
        };

        // start thread for demo
        new Thread(new Runnable() { public void run() { startDemo(); } }).start();
    }
    
    public native void startDemo();
    public native void stopDemo();
    
    static { System.loadLibrary("demobasics"); }
    
    public void setText(String text)
    {
    	mHandler.sendMessage(mHandler.obtainMessage(0, text));
    }

    public void onDemoStopped()
    {
    	mHandler.sendMessage(mHandler.obtainMessage(0, "demo stopped"));
    }
    
    private Button mStopBtn;
    private Handler mHandler;
    private TextView mTextView;
}