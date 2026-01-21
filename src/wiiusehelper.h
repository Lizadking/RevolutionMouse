/*
*
*
*
*/


short any_wiimote_connected(wiimote** wm, int wiimotes) 
{
	int i;
	if (!wm) {
		return 0;
	}

	for (i = 0; i < wiimotes; i++) {
		if (wm[i] && WIIMOTE_IS_CONNECTED(wm[i])) {
			return 1;
		}
	}

	return 0;
}

void handle_disconnect(wiimote* wm) 
{
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}

void handle_ctrl_status(struct wiimote_t* wm) 
{
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}

void handle_read(struct wiimote_t* wm, byte* data, unsigned short len) 
{
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%x ", data[i]);
	}
	printf("\n\n");
}


void handle_event(struct wiimote_t* wm,VirtualDeviceNix * virtualDev) 
{
   
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	/*if a button is pressed, report it */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_A)) 
    {
		printf("A just pressed\n");
        virtualDev->pressWiiKey(WII_A);
        std::cout<<virtualDev->getProfileManager()->getCurrentProfile()->getProfileName()<<std::endl;
		
	}
    
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B)) {
		printf("B pressed\n");
        virtualDev->pressWiiKey(WII_B);

	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		printf("UP pressed\n");
        virtualDev->pressWiiKey(WII_UP);
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN)){
		printf("DOWN pressed\n");
        virtualDev->pressWiiKey(WII_DOWN);
	}
		
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	{
		printf("LEFT pressed\n");
        virtualDev->pressWiiKey(WII_LEFT);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	{
		printf("RIGHT pressed\n");
        virtualDev->pressWiiKey(WII_RIGHT);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	{
		printf("MINUS pressed\n");
        virtualDev->pressWiiKey(WII_MINUS);
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	{
		printf("PLUS pressed\n");
        virtualDev->pressWiiKey(WII_PLUS);
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)) {
		printf("ONE pressed\n");
        virtualDev->pressWiiKey(WII_ONE);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		printf("TWO pressed\n");
        virtualDev->pressWiiKey(WII_TWO);
		
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	{
		printf("HOME pressed\n");
        virtualDev->getProfileManager()->changeProfile();
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS)) 
	{
		//wiiuse_set_ir(wm, 0);
	}


	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS)) 
	{
		//wiiuse_set_ir(wm, 1);

		
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B)) 
	{
		//wiiuse_toggle_rumble(wm);
	}
        

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP)) {
		//wiiuse_set_ir(wm, 1);
	}
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN)) {
		//wiiuse_set_ir(wm, 0);
	}

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_TWO)) {
		wiiuse_set_motion_plus(wm, 0); // off
	}
	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) 
	{
			
			
		
        
	}

}