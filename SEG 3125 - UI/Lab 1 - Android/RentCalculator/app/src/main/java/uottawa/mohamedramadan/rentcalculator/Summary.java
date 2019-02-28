package uottawa.mohamedramadan.rentcalculator;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Summary extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_summary);

        // getIntent() is a method from the started activity
        Intent myIntent = getIntent(); // gets the previously created intent
        String simple = myIntent.getStringExtra("simpleResults"); // will return "FirstKeyValue"
        final String detailedResult = myIntent.getStringExtra("complexResults"); // will return "SecondKeyValue"

        TextView simpleView = (TextView) findViewById(R.id.summary_textView);
        simpleView.setText(simple);

        final Button btnBack = findViewById(R.id.summary_button_back);
        // Set Button Listener
        btnBack.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                finish();
            }
        });

        final Button btnDetails = findViewById(R.id.summary_button_detailed);
        // Set Button Listener
        btnDetails.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                Intent details = new Intent(Summary.this, Details.class);
                details.putExtra("details",detailedResult);
                startActivity(details);
                finish();
            }
        });
    }
}
