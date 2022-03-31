package com.shuaijun.live

import android.os.Bundle
import android.os.Environment
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.shuaijun.live.databinding.ActivityMainBinding
import java.lang.Thread.sleep
import java.util.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method

    }

    override fun onStart() {
        super.onStart()


        val client1 = createNew("rtsp://admin:123456@192.168.1.10:554/stream0", "progName10");
        val client2 = createNew("rtsp://admin:123456@192.168.1.11:554/stream0", "progName11");

        Thread {
            getExternalFilesDir(Environment.DIRECTORY_MOVIES)?.let {
                Log.d("TAG", it.absolutePath)
            }
            openURL(client1)
        }.start()

        Thread {
            openURL(client2)
        }.start()

        Timer().schedule(object : TimerTask() {
            override fun run() {
                close(client1)
                close(client2)
            }
        }, 10_000)
    }

    /**
     * A native method that is implemented by the 'live' native library,
     * which is packaged with this application.
     */
    private external fun createNew(rtspUrl: String, progName: String): Long

    private external fun openURL(rtspClient: Long)

    private external fun close(rtspClient: Long)

    companion object {
        // Used to load the 'live' library on application startup.
        init {
            System.loadLibrary("live")
        }
    }
}