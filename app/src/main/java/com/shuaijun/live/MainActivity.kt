package com.shuaijun.live

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.shuaijun.live.databinding.ActivityMainBinding
import java.lang.Thread.sleep

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

        Thread {
            sleep(3000)
            stringFromJNI() }.start()
    }

    /**
     * A native method that is implemented by the 'live' native library,
     * which is packaged with this application.
     */
    private external fun stringFromJNI()

    companion object {
        // Used to load the 'live' library on application startup.
        init {
            System.loadLibrary("live")
        }
    }
}