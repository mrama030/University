package uottawa.mohamedramadan.rentcalculator;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Details extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_details);

        Intent myIntent = getIntent(); // gets the previously created intent
        String detailedResult = myIntent.getStringExtra("details");

        TextView view = (TextView) findViewById(R.id.details_textView);
        view.setText(detailedResult);

        //Log.e("DETAILS:", detailedResult);

        final Button btnBack = findViewById(R.id.details_button_back);
        // Set Button Listener
        btnBack.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                finish();
            }
        });
    }
}
