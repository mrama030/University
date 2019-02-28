package uottawa.mohamedramadan.rentcalculator;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.Icon;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.text.TextUtils;
import android.widget.Toolbar;

import static android.text.TextUtils.isDigitsOnly;

public class WelcomeScreen extends AppCompatActivity
{
    public String _detailedResults = "";

    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
        MenuInflater mMenuInflater = getMenuInflater();
        mMenuInflater.inflate(R.menu.my_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
        int id = item.getItemId();
        if (id == R.id.action_setting)
        {
            // open settings page...
            Intent settings = new Intent(WelcomeScreen.this, ActivityForSettings.class);
            startActivity(settings);
            return true;
        }

        return false;
    }

    public class calculateTask implements Runnable
    {
        // Calculate Event Task
        @Override
        public void run()
        {
            //region User validation
            Log.e("Button Click", "Calculate Button was clicked successfully.");

            boolean cleanInput = true;
            EditText numberRooms = (EditText) findViewById(R.id.textRooms);
            EditText rent = (EditText) findViewById(R.id.textRent);

            LinearLayout room1 = (LinearLayout) findViewById(R.id.verticalLayoutRoom1);
            LinearLayout room2 = (LinearLayout) findViewById(R.id.verticalLayoutRoom2);
            LinearLayout room3 = (LinearLayout) findViewById(R.id.verticalLayoutRoom3);
            LinearLayout room4 = (LinearLayout) findViewById(R.id.verticalLayoutRoom4);
            LinearLayout room5 = (LinearLayout) findViewById(R.id.verticalLayoutRoom5);

            try
            {
                //region Residence Info

                // Validate number of rooms.
                if (numberRooms.getText().toString().matches(""))
                {
                    numberRooms.setError("Required.");
                    cleanInput = false;
                }
                else if (Integer.parseInt(numberRooms.getText().toString()) > 5 || Integer.parseInt(numberRooms.getText().toString()) < 1)
                {
                    numberRooms.setError("Must be between 1 and 5.");
                    cleanInput = false;
                }
                // Validate monthly rent amount.
                if (rent.getText().toString().matches(""))
                {
                    rent.setError("Required.");
                    cleanInput = false;
                }
                else if (Integer.parseInt(rent.getText().toString()) < 1)
                {
                    rent.setError("Must be positive.");
                    cleanInput = false;
                }
                //endregion

                // Validate each room's contents if it is visible.

                //region ROOM1

                if (room1.getVisibility() == View.VISIBLE)
                {
                    EditText room1People = (EditText) findViewById(R.id.textRoom1People);
                    EditText room1Size = (EditText) findViewById(R.id.textRoom1Size);
                    EditText room1Name1 = (EditText) findViewById(R.id.textRoom1Name1);
                    EditText room1Name2 = (EditText) findViewById(R.id.textRoom1Name2);

                    // # of people
                    if (room1People.getText().toString().matches(""))
                    {
                        room1People.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room1People.getText().toString()) < 1 || Integer.parseInt(room1People.getText().toString()) > 2)
                    {
                        room1People.setError("Must be between 1 and 2.");
                        cleanInput = false;
                    }

                    // room size
                    if (room1Size.getText().toString().matches(""))
                    {
                        room1Size.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room1Size.getText().toString()) < 1)
                    {
                        room1Size.setError("Must be positive.");
                        cleanInput = false;
                    }
                    // Occupant of the rooms.
                    if (room1Name1.getText().toString().matches(""))
                    {
                        room1Name1.setError("Required.");
                        cleanInput = false;
                    }

                    if (Integer.parseInt(room1People.getText().toString()) == 2)
                    {
                        if (room1Name2.getText().toString().matches(""))
                        {
                            room1Name2.setError("Required.");
                            cleanInput = false;
                        }
                    }
                }
                //endregion

                //region ROOM2

                if (room2.getVisibility() == View.VISIBLE)
                {
                    EditText room2People = (EditText) findViewById(R.id.textRoom2People);
                    EditText room2Size = (EditText) findViewById(R.id.textRoom2Size);
                    EditText room2Name1 = (EditText) findViewById(R.id.textRoom2Name1);
                    EditText room2Name2 = (EditText) findViewById(R.id.textRoom2Name2);

                    // # of people
                    if (room2People.getText().toString().matches(""))
                    {
                        room2People.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room2People.getText().toString()) < 1 || Integer.parseInt(room2People.getText().toString()) > 2)
                    {
                        room2People.setError("Must be between 1 and 2.");
                        cleanInput = false;
                    }

                    // room size
                    if (room2Size.getText().toString().matches(""))
                    {
                        room2Size.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room2Size.getText().toString()) < 1)
                    {
                        room2Size.setError("Must be positive.");
                        cleanInput = false;
                    }
                    // Occupant of the rooms.
                    if (room2Name1.getText().toString().matches(""))
                    {
                        room2Name1.setError("Required.");
                        cleanInput = false;
                    }

                    if (Integer.parseInt(room2People.getText().toString()) == 2)
                    {
                        if (room2Name2.getText().toString().matches(""))
                        {
                            room2Name2.setError("Required.");
                            cleanInput = false;
                        }
                    }
                }
                //endregion

                //region ROOM3

                if (room3.getVisibility() == View.VISIBLE)
                {
                    EditText room3People = (EditText) findViewById(R.id.textRoom3People);
                    EditText room3Size = (EditText) findViewById(R.id.textRoom3Size);
                    EditText room3Name1 = (EditText) findViewById(R.id.textRoom3Name1);
                    EditText room3Name2 = (EditText) findViewById(R.id.textRoom3Name2);

                    // # of people
                    if (room3People.getText().toString().matches(""))
                    {
                        room3People.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room3People.getText().toString()) < 1 || Integer.parseInt(room3People.getText().toString()) > 2)
                    {
                        room3People.setError("Must be between 1 and 2.");
                        cleanInput = false;
                    }

                    // room size
                    if (room3Size.getText().toString().matches(""))
                    {
                        room3Size.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room3Size.getText().toString()) < 1)
                    {
                        room3Size.setError("Must be positive.");
                        cleanInput = false;
                    }
                    // Occupant of the rooms.
                    if (room3Name1.getText().toString().matches(""))
                    {
                        room3Name1.setError("Required.");
                        cleanInput = false;
                    }

                    if (Integer.parseInt(room3People.getText().toString()) == 2)
                    {
                        if (room3Name2.getText().toString().matches(""))
                        {
                            room3Name2.setError("Required.");
                            cleanInput = false;
                        }
                    }
                }
                //endregion

                //region ROOM4

                if (room4.getVisibility() == View.VISIBLE)
                {
                    EditText room4People = (EditText) findViewById(R.id.textRoom4People);
                    EditText room4Size = (EditText) findViewById(R.id.textRoom4Size);
                    EditText room4Name1 = (EditText) findViewById(R.id.textRoom4Name1);
                    EditText room4Name2 = (EditText) findViewById(R.id.textRoom4Name2);

                    // # of people
                    if (room4People.getText().toString().matches(""))
                    {
                        room4People.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room4People.getText().toString()) < 1 || Integer.parseInt(room4People.getText().toString()) > 2)
                    {
                        room4People.setError("Must be between 1 and 2.");
                        cleanInput = false;
                    }

                    // room size
                    if (room4Size.getText().toString().matches(""))
                    {
                        room4Size.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room4Size.getText().toString()) < 1)
                    {
                        room4Size.setError("Must be positive.");
                        cleanInput = false;
                    }
                    // Occupant of the rooms.
                    if (room4Name1.getText().toString().matches(""))
                    {
                        room4Name1.setError("Required.");
                        cleanInput = false;
                    }

                    if (Integer.parseInt(room4People.getText().toString()) == 2)
                    {
                        if (room4Name2.getText().toString().matches(""))
                        {
                            room4Name2.setError("Required.");
                            cleanInput = false;
                        }
                    }
                }
                //endregion

                //region ROOM5

                if (room5.getVisibility() == View.VISIBLE)
                {
                    EditText room5People = (EditText) findViewById(R.id.textRoom5People);
                    EditText room5Size = (EditText) findViewById(R.id.textRoom5Size);
                    EditText room5Name1 = (EditText) findViewById(R.id.textRoom5Name1);
                    EditText room5Name2 = (EditText) findViewById(R.id.textRoom5Name2);

                    // # of people
                    if (room5People.getText().toString().matches(""))
                    {
                        room5People.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room5People.getText().toString()) < 1 || Integer.parseInt(room5People.getText().toString()) > 2)
                    {
                        room5People.setError("Must be between 1 and 2.");
                        cleanInput = false;
                    }

                    // room size
                    if (room5Size.getText().toString().matches(""))
                    {
                        room5Size.setError("Required.");
                        cleanInput = false;
                    }
                    else if (Integer.parseInt(room5Size.getText().toString()) < 1)
                    {
                        room5Size.setError("Must be positive.");
                        cleanInput = false;
                    }
                    // Occupant of the rooms.
                    if (room5Name1.getText().toString().matches(""))
                    {
                        room5Name1.setError("Required.");
                        cleanInput = false;
                    }

                    if (Integer.parseInt(room5People.getText().toString()) == 2)
                    {
                        if (room5Name2.getText().toString().matches(""))
                        {
                            room5Name2.setError("Required.");
                            cleanInput = false;
                        }
                    }
                }
                //endregion

            }
            catch (Exception e)
            {
                Log.e("exception was caught:", e.getMessage());
            }
            //endregion

            if (cleanInput)
            {
                // CALCULATE RENT AND DISPLAY NEW PAGE
                try
                {
                    // calculations

                    String simpleResult = "";
                    String complexResult = "";

                    String currencySymbol = "$";
                    String measurementUnit = "sq. ft.";


                    // Obtain user inputs
                    int numRooms = Integer.parseInt(((EditText)findViewById(R.id.textRooms)).getText().toString());
                    int monthlyRent = Integer.parseInt(((EditText)findViewById(R.id.textRent)).getText().toString());

                    int room1Size = Integer.parseInt(((EditText)findViewById(R.id.textRoom1Size)).getText().toString());
                    int room1NumPeople = Integer.parseInt(((EditText)findViewById(R.id.textRoom1People)).getText().toString());
                    String room1Name1 = ((EditText)findViewById(R.id.textRoom1Name1)).getText().toString();
                    String room1Name2 = ((EditText)findViewById(R.id.textRoom1Name2)).getText().toString();
                    String room1Type = ((Spinner)findViewById(R.id.spinnerRoom1Type)).getSelectedItem().toString();

                    int room2Size = 0;
                    int room2NumPeople = 0;
                    String room2Name1 = null;
                    String room2Name2 = null;
                    String room2Type = null;

                    int room3Size = 0;
                    int room3NumPeople = 0;
                    String room3Name1 = null;
                    String room3Name2 = null;
                    String room3Type = null;

                    int room4Size = 0;
                    int room4NumPeople = 0;
                    String room4Name1 = null;
                    String room4Name2 = null;
                    String room4Type = null;

                    int room5Size = 0;
                    int room5NumPeople = 0;
                    String room5Name1 = null;
                    String room5Name2 = null;
                    String room5Type = null;

                    if (numRooms >= 2)
                    {
                        room2Size = Integer.parseInt(((EditText)findViewById(R.id.textRoom2Size)).getText().toString());
                        room2NumPeople = Integer.parseInt(((EditText)findViewById(R.id.textRoom2People)).getText().toString());
                        room2Name1 = ((EditText)findViewById(R.id.textRoom2Name1)).getText().toString();
                        room2Name2 = ((EditText)findViewById(R.id.textRoom2Name2)).getText().toString();
                        room2Type = ((Spinner)findViewById(R.id.spinnerRoom2Type)).getSelectedItem().toString();
                    }

                    if (numRooms >= 3)
                    {
                        room3Size = Integer.parseInt(((EditText)findViewById(R.id.textRoom3Size)).getText().toString());
                        room3NumPeople = Integer.parseInt(((EditText)findViewById(R.id.textRoom3People)).getText().toString());
                        room3Name1 = ((EditText)findViewById(R.id.textRoom3Name1)).getText().toString();
                        room3Name2 = ((EditText)findViewById(R.id.textRoom3Name2)).getText().toString();
                        room3Type = ((Spinner)findViewById(R.id.spinnerRoom3Type)).getSelectedItem().toString();
                    }

                    if (numRooms >= 4)
                    {
                        room4Size = Integer.parseInt(((EditText)findViewById(R.id.textRoom4Size)).getText().toString());
                        room4NumPeople = Integer.parseInt(((EditText)findViewById(R.id.textRoom4People)).getText().toString());
                        room4Name1 = ((EditText)findViewById(R.id.textRoom4Name1)).getText().toString();
                        room4Name2 = ((EditText)findViewById(R.id.textRoom4Name2)).getText().toString();
                        room4Type = ((Spinner)findViewById(R.id.spinnerRoom4Type)).getSelectedItem().toString();
                    }

                    if (numRooms == 5)
                    {
                        room5Size = Integer.parseInt(((EditText)findViewById(R.id.textRoom5Size)).getText().toString());
                        room5NumPeople = Integer.parseInt(((EditText)findViewById(R.id.textRoom5People)).getText().toString());
                        room5Name1 = ((EditText)findViewById(R.id.textRoom5Name1)).getText().toString();
                        room5Name2 = ((EditText)findViewById(R.id.textRoom5Name2)).getText().toString();
                        room5Type = ((Spinner)findViewById(R.id.spinnerRoom5Type)).getSelectedItem().toString();
                    }

                    int totalSize = room1Size + room2Size + room3Size + room4Size + room5Size;

                    String room1Names = room1Name1;
                    String room2Names = room2Name1;
                    String room3Names = room3Name1;
                    String room4Names = room4Name1;
                    String room5Names = room5Name1;

                    if (room1NumPeople == 2) {room1Names += (" and " + room1Name2);}
                    if (room2NumPeople == 2) {room2Names += (" and " + room2Name2);}
                    if (room3NumPeople == 2) {room3Names += (" and " + room3Name2);}
                    if (room4NumPeople == 2) {room4Names += (" and " + room4Name2);}
                    if (room5NumPeople == 2) {room5Names += (" and " + room5Name2);}


                    simpleResult = room1Names + " must pay " + Math.round((((float)room1Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    if (room2Names != null)
                        simpleResult += room2Names + " must pay " + Math.round((((float)room2Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    if (room3Names != null)
                        simpleResult += room3Names + " must pay " + Math.round((((float)room3Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    if (room4Names != null)
                        simpleResult += room4Names + " must pay " + Math.round((((float)room4Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    if (room5Names != null)
                        simpleResult += room5Names + " must pay " + Math.round((((float)room5Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";

                    simpleResult += "\nTotal Monthly Cost: " + monthlyRent + " " + currencySymbol + ".";
                    simpleResult += "\nTotal Bedroom Space: " + totalSize + " " + measurementUnit + ".";

                    int percentageRoom1 = (int)(100*((float)room1Size/totalSize));
                    complexResult = "Since the " + room1Type + " has " + room1Size + " " + measurementUnit + ", which corresponds to " + percentageRoom1
                            + "% of the bedroom area, the rent is: " + Math.round((((float)room1Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";

                    if (numRooms >= 2)
                    {
                        int percentageRoom2 = (int)(100*((float)room2Size/totalSize));
                        complexResult += "Since the " + room2Type + " has " + room2Size + " " + measurementUnit + ", which corresponds to " + percentageRoom2
                                + "% of the bedroom area, the rent is: " + Math.round((((float)room2Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    }

                    if (numRooms >= 3)
                    {
                        int percentageRoom3 = (int)(100*((float)room3Size/totalSize));
                        complexResult += "Since the " + room3Type + " has " + room3Size + " " + measurementUnit + ", which corresponds to " + percentageRoom3
                                + "% of the bedroom area, the rent is: " + Math.round((((float)room3Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    }

                    if (numRooms >= 4)
                    {
                        int percentageRoom4 = (int)(100*((float)room4Size/totalSize));
                        complexResult += "Since the " + room4Type + " has " + room4Size + " " + measurementUnit + ", which corresponds to " + percentageRoom4
                                + "% of the bedroom area, the rent is: " + Math.round((((float)room4Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    }

                    if (numRooms == 5)
                    {
                        int percentageRoom5 = (int)(100*((float)room5Size/totalSize));
                        complexResult += "Since the " + room5Type + " has " + room5Size + " " + measurementUnit + ", which corresponds to " + percentageRoom5
                                + "% of the bedroom area, the rent is: " + Math.round((((float)room5Size/totalSize)*monthlyRent)) + " " + currencySymbol + ".\n";
                    }

                    _detailedResults = complexResult;

                    Intent myIntent = new Intent(WelcomeScreen.this, Summary.class);
                    myIntent.putExtra("simpleResults",simpleResult);
                    myIntent.putExtra("complexResults",complexResult);
                    startActivity(myIntent);
                }
                catch(Exception e)
                {
                    Log.e("displaying results:", e.getMessage());
                }
            }
            else {return;}
        }
    }

    public class numberRoomsChangeTask implements Runnable
    {
        public int count;
        public numberRoomsChangeTask(int c)
        {
            this.count=c;
        }
        // Event runs when the text value for number of rooms changes.
        @Override
        public void run()
        {
            try
            {
                Button btnCalculate = findViewById(R.id.buttonCalculate);
                btnCalculate.setEnabled(false);
                EditText numberRooms = (EditText) findViewById(R.id.textRooms);
                LinearLayout room1 = (LinearLayout) findViewById(R.id.verticalLayoutRoom1);
                LinearLayout room2 = (LinearLayout) findViewById(R.id.verticalLayoutRoom2);
                LinearLayout room3 = (LinearLayout) findViewById(R.id.verticalLayoutRoom3);
                LinearLayout room4 = (LinearLayout) findViewById(R.id.verticalLayoutRoom4);
                LinearLayout room5 = (LinearLayout) findViewById(R.id.verticalLayoutRoom5);

                // Text box is null or empty.
                if (this.count==0)
                {
                    room1.setVisibility(View.GONE);
                    room2.setVisibility(View.GONE);
                    room3.setVisibility(View.GONE);
                    room4.setVisibility(View.GONE);
                    room5.setVisibility(View.GONE);
                    numberRooms.setError("Must be between 1 and 5.");
                    return;
                }
                // Text box is between 1 and 5. VALID
                else if (Integer.parseInt(numberRooms.getText().toString()) <= 5 && Integer.parseInt(numberRooms.getText().toString()) >= 1)
                {
                    btnCalculate.setEnabled(true);

                    if (Integer.parseInt(numberRooms.getText().toString()) == 1) {
                        room1.setVisibility(View.VISIBLE);
                        room2.setVisibility(View.GONE);
                        room3.setVisibility(View.GONE);
                        room4.setVisibility(View.GONE);
                        room5.setVisibility(View.GONE);
                    } else if (Integer.parseInt(numberRooms.getText().toString()) == 2) {
                        room1.setVisibility(View.VISIBLE);
                        room2.setVisibility(View.VISIBLE);
                        room3.setVisibility(View.GONE);
                        room4.setVisibility(View.GONE);
                        room5.setVisibility(View.GONE);
                    } else if (Integer.parseInt(numberRooms.getText().toString()) == 3) {
                        room1.setVisibility(View.VISIBLE);
                        room2.setVisibility(View.VISIBLE);
                        room3.setVisibility(View.VISIBLE);
                        room4.setVisibility(View.GONE);
                        room5.setVisibility(View.GONE);
                    } else if (Integer.parseInt(numberRooms.getText().toString()) == 4) {
                        room1.setVisibility(View.VISIBLE);
                        room2.setVisibility(View.VISIBLE);
                        room3.setVisibility(View.VISIBLE);
                        room4.setVisibility(View.VISIBLE);
                        room5.setVisibility(View.GONE);
                    } else if (Integer.parseInt(numberRooms.getText().toString()) == 5) {
                        room1.setVisibility(View.VISIBLE);
                        room2.setVisibility(View.VISIBLE);
                        room3.setVisibility(View.VISIBLE);
                        room4.setVisibility(View.VISIBLE);
                        room5.setVisibility(View.VISIBLE);
                    }
                    return;
                }
                // Value is not between 1 and 5 or is not an integer.
                else {
                    room1.setVisibility(View.GONE);
                    room2.setVisibility(View.GONE);
                    room3.setVisibility(View.GONE);
                    room4.setVisibility(View.GONE);
                    room5.setVisibility(View.GONE);
                    numberRooms.setError("Must be between 1 and 5.");
                    return;
                }
            }
            catch (Exception e)
            {
                Log.e("exception occurred: ", e.getMessage());
            }
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_welcome_screen);

        //region Setup spinners
        Spinner typeRoom1 = (Spinner) findViewById(R.id.spinnerRoom1Type);
        Spinner typeRoom2 = (Spinner) findViewById(R.id.spinnerRoom2Type);
        Spinner typeRoom3 = (Spinner) findViewById(R.id.spinnerRoom3Type);
        Spinner typeRoom4 = (Spinner) findViewById(R.id.spinnerRoom4Type);
        Spinner typeRoom5 = (Spinner) findViewById(R.id.spinnerRoom5Type);

        ArrayAdapter<String> myAdapter1 = new ArrayAdapter<String>(WelcomeScreen.this,
                android.R.layout.simple_list_item_1, getResources().getStringArray(R.array.roomTypes));
        myAdapter1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        typeRoom1.setAdapter(myAdapter1);
        typeRoom2.setAdapter(myAdapter1);
        typeRoom3.setAdapter(myAdapter1);
        typeRoom4.setAdapter(myAdapter1);
        typeRoom5.setAdapter(myAdapter1);
        //endregion

        //region Hide 5 room input layouts
        LinearLayout room1 = (LinearLayout) findViewById(R.id.verticalLayoutRoom1);
        LinearLayout room2 = (LinearLayout) findViewById(R.id.verticalLayoutRoom2);
        LinearLayout room3 = (LinearLayout) findViewById(R.id.verticalLayoutRoom3);
        LinearLayout room4 = (LinearLayout) findViewById(R.id.verticalLayoutRoom4);
        LinearLayout room5 = (LinearLayout) findViewById(R.id.verticalLayoutRoom5);
        room1.setVisibility(View.GONE);
        room2.setVisibility(View.GONE);
        room3.setVisibility(View.GONE);
        room4.setVisibility(View.GONE);
        room5.setVisibility(View.GONE);
        //endregion

        // Obtain text box for number of rooms.
        EditText numberRooms = (EditText) findViewById(R.id.textRooms);

        final Button btnCalculate = findViewById(R.id.buttonCalculate);

        // Disable button
        btnCalculate.setEnabled(false);
        // Set Button Listener
        btnCalculate.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                calculateTask calcThread = new calculateTask();
                calcThread.run();
            }
        });
        // Set text change listener for number of rooms.
        numberRooms.addTextChangedListener(new TextWatcher()
        {
            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count)
            {
                numberRoomsChangeTask textTask = new numberRoomsChangeTask(count);
                textTask.run();
                return;
            }
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {
                // TODO Auto-generated method stub
                return;
            }
            @Override
            public void afterTextChanged(Editable arg0) {
                // TODO Auto-generated method stub
                return;
            }
        });
    }

}
