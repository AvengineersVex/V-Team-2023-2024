#include "main.h"


lv_obj_t * redLeftButton;
lv_obj_t * redLeftButtonLabel;
lv_obj_t * redRightButton;
lv_obj_t * redRightButtonLabel;
lv_obj_t * blueLeftButton;
lv_obj_t * blueLeftButtonLabel;
lv_obj_t * blueRightButton;
lv_obj_t * blueRightButtonLabel;


lv_obj_t * selectionInfoLabel;

lv_style_t redButtonStyleREL; //relesed style
lv_style_t redButtonStylePR; //pressed style
lv_style_t blueButtonStyleREL; //relesed style
lv_style_t blueButtonStylePR; //pressed style
lv_style_t screenStyle;

int auton_location = -1;

enum BUTTONS {
    RED_LEFT = 0,
    RED_RIGHT = 1,
    BLUE_LEFT = 2,
    BLUE_RIGHT = 3,
};


static lv_res_t btn_click_action(lv_obj_t * btn)
{
    uint8_t id = lv_obj_get_free_num(btn); //id usefull when there are multiple buttons

    auton_location = -1;
    char buffer[100];
    if (id == BUTTONS::RED_LEFT) {
        sprintf(buffer, "Red Left Selected @ %ims", pros::millis());
        auton_location = BUTTONS::RED_LEFT;
    } else if (id == BUTTONS::RED_RIGHT) {
        sprintf(buffer, "Red Right Selected @ %ims", pros::millis());
        auton_location = BUTTONS::RED_RIGHT;
    } else if (id == BUTTONS::BLUE_LEFT) {
        sprintf(buffer, "Blue Left Selected @ %ims", pros::millis());
        auton_location = BUTTONS::BLUE_LEFT;
    } else if (id == BUTTONS::BLUE_RIGHT) {
        sprintf(buffer, "Blue Right Selected @ %ims", pros::millis());
        auton_location = BUTTONS::BLUE_RIGHT;
    } else {
        sprintf(buffer, "No Selection @ %ims", pros::millis());
    }
    
    lv_label_set_text(selectionInfoLabel, buffer);

    // background
    if (id == BUTTONS::BLUE_LEFT || id == BUTTONS::BLUE_RIGHT) {
        lv_style_copy(&screenStyle, &lv_style_plain);
        screenStyle.body.main_color = LV_COLOR_MAKE(96, 95 , 94);
        screenStyle.body.grad_color = LV_COLOR_MAKE(39, 93, 173);
        //     screenStyle.body.grad_color = LV_COLOR_MAKE(153, 13, 53); // red
        lv_obj_set_style(lv_scr_act(), &screenStyle);
    } else if (id == BUTTONS::RED_LEFT || id == BUTTONS::RED_RIGHT) {
        lv_style_copy(&screenStyle, &lv_style_plain);
        screenStyle.body.main_color = LV_COLOR_MAKE(96, 95 , 94);
        // screenStyle.body.grad_color = LV_COLOR_MAKE(39, 93, 173); // blue
        screenStyle.body.grad_color = LV_COLOR_MAKE(153, 13, 53);
        lv_obj_set_style(lv_scr_act(), &screenStyle);
    }
    

    return LV_RES_OK;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    lv_style_copy(&redButtonStyleREL, &lv_style_plain);
    redButtonStyleREL.body.main_color = LV_COLOR_MAKE(219, 50, 77);
    redButtonStyleREL.body.grad_color = LV_COLOR_MAKE(219, 50, 77);
    redButtonStyleREL.body.radius = 0;
    redButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&redButtonStylePR, &lv_style_plain);
    redButtonStylePR.body.main_color = LV_COLOR_MAKE(166, 38, 57);
    redButtonStylePR.body.grad_color = LV_COLOR_MAKE(219, 50, 77);
    redButtonStylePR.body.radius = 0;
    redButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&blueButtonStyleREL, &lv_style_plain);
    blueButtonStyleREL.body.main_color = LV_COLOR_MAKE(40, 175, 176);
    blueButtonStyleREL.body.grad_color = LV_COLOR_MAKE(40, 175, 176);
    blueButtonStyleREL.body.radius = 0;
    blueButtonStyleREL.text.color = LV_COLOR_MAKE(255, 255, 255);

    lv_style_copy(&blueButtonStylePR, &lv_style_plain);
    blueButtonStylePR.body.main_color = LV_COLOR_MAKE(25, 100, 126);
    blueButtonStylePR.body.grad_color = LV_COLOR_MAKE(40, 175, 176);
    blueButtonStylePR.body.radius = 0;
    blueButtonStylePR.text.color = LV_COLOR_MAKE(255, 255, 255);


    // left red button
    redLeftButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(redLeftButton, BUTTONS::RED_LEFT); //set button is to 0
    lv_btn_set_action(redLeftButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_REL, &redButtonStyleREL); //set the relesed style
    lv_btn_set_style(redLeftButton, LV_BTN_STYLE_PR, &redButtonStylePR); //set the pressed style
    lv_obj_set_size(redLeftButton, 200, 50); //set the button size
    lv_obj_align(redLeftButton, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 10, -10); //set the position to top mid

    redLeftButtonLabel = lv_label_create(redLeftButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(redLeftButtonLabel, "Red left"); //sets label text


    // red right button

    redRightButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(redRightButton, BUTTONS::RED_RIGHT); //set button is to 0
    lv_btn_set_action(redRightButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_REL, &redButtonStyleREL); //set the relesed style
    lv_btn_set_style(redRightButton, LV_BTN_STYLE_PR, &redButtonStylePR); //set the pressed style
    lv_obj_set_size(redRightButton, 200, 50); //set the button size
    lv_obj_align(redRightButton, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10); //set the position to top mid

    redRightButtonLabel = lv_label_create(redRightButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(redRightButtonLabel, "Red right"); //sets label text

    // left blue button
    blueLeftButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(blueLeftButton, BUTTONS::BLUE_LEFT); //set button is to 0
    lv_btn_set_action(blueLeftButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_REL, &blueButtonStyleREL); //set the relesed style
    lv_btn_set_style(blueLeftButton, LV_BTN_STYLE_PR, &blueButtonStylePR); //set the pressed style
    lv_obj_set_size(blueLeftButton, 200, 50); //set the button size
    lv_obj_align(blueLeftButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10); //set the position to top mid

    blueLeftButtonLabel = lv_label_create(blueLeftButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(blueLeftButtonLabel, "Blue left"); //sets label text


    // blue right button

    blueRightButton = lv_btn_create(lv_scr_act(), NULL); //create button, lv_scr_act() is deafult screen object
    lv_obj_set_free_num(blueRightButton, BUTTONS::BLUE_RIGHT); //set button is to 0
    lv_btn_set_action(blueRightButton, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_REL, &blueButtonStyleREL); //set the relesed style
    lv_btn_set_style(blueRightButton, LV_BTN_STYLE_PR, &blueButtonStylePR); //set the pressed style
    lv_obj_set_size(blueRightButton, 200, 50); //set the button size
    lv_obj_align(blueRightButton, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 10); //set the position to top mid

    blueRightButtonLabel = lv_label_create(blueRightButton, NULL); //create label and puts it inside of the button
    lv_label_set_text(blueRightButtonLabel, "Blue right"); //sets label text


    selectionInfoLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
    lv_label_set_text(selectionInfoLabel, "Buttons"); //sets label text
    lv_obj_align(selectionInfoLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0); //set the position to center

    // background
    lv_style_copy(&screenStyle, &lv_style_plain);
    screenStyle.body.main_color = LV_COLOR_MAKE(96, 95 , 94);
    screenStyle.body.grad_color = LV_COLOR_MAKE(96, 95, 94);
    lv_obj_set_style(lv_scr_act(), &screenStyle);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
            .withMotors({11,12},{-18,-20})
            // Green gearset, 4 in wheel diam, 11.5 in wheel track
            .withDimensions(AbstractMotor::gearset::green, {{4.1875_in, 10.575_in}, imev5GreenTPR})
            .build();
    
    std::shared_ptr<AsyncMotionProfileController> profileController =
    AsyncMotionProfileControllerBuilder()
        .withLimits({
        1.0, // Maximum linear velocity of the Chassis in m/s
        2.0, // Maximum linear acceleration of the Chassis in m/s/s
        10.0 // Maximum linear jerk of the Chassis in m/s/s/s
        })
        .withOutput(drive)
        .buildMotionProfileController();

    profileController->generatePath({
        {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
        {35_in, 22_in, 0_deg}}, // The next point in the profile, 3 feet forward
        "score_preload" // Profile name
    );

    // profileController->generatePath({
    //     {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    //     {3_in, 0_in, 0_deg}}, // The next point in the profile, 3 feet forward
    //     "score_bar_1" // Profile name
    // );
    

    // profileController->generatePath({
    //     {0_ft, 0_ft, 0_deg},  // Profile starting position, this will normally be (0, 0, 0)
    //     {0_in, 5_in, 0_deg}},
    //     "touch_bar_forwardPartTwo" // Profile name
    // );


    
    drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
    // if(auton_location == 0){
    //     drive->moveDistance(-3_in);
    //     // drive->waitUntilSettled();
    //     drive->turnAngle(-90_deg);
    //     // drive->waitUntilSettled();
    //     drive->moveDistance(3_in);
    //     // drive->waitUntilSettled();
    // }
    // drive->setMaxVelocity(200);

    // drive->moveDistance(6_in);
    // drive->turnAngle(45_deg);
    // drive->moveDistance(30_in);
    // drive->turnAngle(-45_deg);
    // drive->moveDistance(15_in);
    // drive->moveDistance(-15_in);
    // drive->turnAngle(45_deg);
    // drive->moveDistance(-34_in);
    // drive->turnAngle(45_deg);
    // drive->moveDistance(-36_in);
    // drive->turnAngle(-135_deg);
    // drive->moveDistance(36_in);
    // drive->turnAngle(45_deg);

    if (auton_location == BUTTONS::RED_RIGHT || auton_location == BUTTONS::BLUE_RIGHT) {
        profileController->setTarget("score_preload", false, false);
        profileController->waitUntilSettled();
        profileController->setTarget("score_preload", true, true);
        profileController->waitUntilSettled();
        drive->moveDistance(2_in);
        drive->turnAngle(90_deg);
        drive->moveDistance(-34_in);
    } else if (auton_location == BUTTONS::RED_LEFT || auton_location == BUTTONS::BLUE_LEFT) {
        profileController->setTarget("score_preload", false, true);
        profileController->waitUntilSettled();
        profileController->setTarget("score_preload", true, false);
        profileController->waitUntilSettled();
    }
    
    

            
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    std::shared_ptr<ChassisController> drive = ChassisControllerBuilder()
            .withMotors({11,12},{-18,-20})
            // Green gearset, 4 in wheel diam, 11.5 in wheel track
            .withDimensions(AbstractMotor::gearset::green, {{4_in, 14.5_in}, imev5GreenTPR})
            .build();
    
    auto launchMotor = Motor(6, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
    auto intakeMotor = Motor(10, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    auto wingsMotor = Motor(15, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

    
    
    launchMotor.setBrakeMode(AbstractMotor::brakeMode::coast);
    int checkStopped = -1;
    bool isIntakeOn = false;
    intakeMotor.moveVelocity(0);

	drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::brake);
    ControllerButton wingsOpenButton(ControllerDigital::left);
    ControllerButton wingsCloseButton(ControllerDigital::right);

    ControllerButton launchButton(ControllerDigital::X);
    

    ControllerButton intakeButton(ControllerDigital::R1);
    ControllerButton outtakeButton(ControllerDigital::L1);
    
    
    Controller controller;

    while (true) {
        // Arcade drive with the left stick
        drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                                  controller.getAnalog(ControllerAnalog::rightX));
        
        // if (launchButton.changedToPressed()) {
        //     launchMotor.moveRelative(360, 100);
        //     checkStopped = 10;
        // }

        if (intakeButton.changed() || outtakeButton.changed()) {
            if (intakeButton.isPressed()) {
                intakeMotor.moveVelocity(300);
            } else if (outtakeButton.isPressed()) {
                intakeMotor.moveVelocity(-300);
            } else {
                intakeMotor.moveVelocity(0);
            }
        }

        
        if (wingsOpenButton.changedToPressed()) {
            wingsMotor.moveRelative(150, 100);
        } else if (wingsCloseButton.changedToPressed()) {
            wingsMotor.moveRelative(-150, 400);
        }

        // if (checkStopped > 0) {
        //     checkStopped--;
        // }
        // if (checkStopped == 0) {
        //     if (launchMotor.getActualVelocity()==0) {
        //         launchMotor.moveVoltage(0);
        //         checkStopped = -1;
        //     }
        // }

        pros::delay(10);
    }
}

/*
 * vision::signature SIG_1 (1, 11897, 12435, 12166, -2389, -1719, -2054, 5.100, 0);
vision::signature SIG_2 (2, -3619, -2679, -3148, 5957, 7813, 6886, 3.000, 0);
vision::signature SIG_3 (3, -5479, -4769, -5124, -7207, -6553, -6880, 3.000, 0);
vision::signature SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_6 (6, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature SIG_7 (7, 0, 0, 0, 0, 0, 0, 3.000, 0);
vex::vision vision1 ( vex::PORT1, 45, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7 );
 */