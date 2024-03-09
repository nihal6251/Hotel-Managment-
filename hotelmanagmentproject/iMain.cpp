#include "iGraphics.h"
#include <string.h>

char adminID[100], adminP[100];

int adminlen = 0;
int passlen = 0;

int avr;
int wp = 0;
int aID = 0, aIDs = 0;
int aP = 0, aPs = 0;
int adminL = 0;
int home = 0;
int contact = 0;
int aLtoaD = 0; // proceed to admin dashboard from adminL
int sbookings = 0;
int arb = 0;
int aTs = 0;
int addstaff, addstaffdone;
int showstaff;
int rfb = 0;
int ps = 0, cs = 0, hs = 0, d1 = 0, d2 = 0, d3 = 0;
int bpage = 0;
int rmns = 0;
int bdone = 0;
int rstrnt = 0;
int r1 = 0;
int r2 = 0;

// text boxes
char name[20];
int namelen, n = 0, ns = 0;
char phone[20];
int phonelen, phn = 0, phns = 0;
char room_no[20];
int roomnolen, roomno = 0, room_nos = 0;
char check_in[20];
int checkinlen, checkin = 0, checkins = 0;
char check_out[20];
int checkoutlen, checkout = 0, checkouts = 0;
char staff_name[20];
int stnlen, stn = 0, stns = 0;
char staff_phone[20];
int stphnlen, stphn = 0, stphns = 0;
char staff_room[20];
int strrmlen, strrm = 0, strrms = 0;

int roombooked = 0;
char roomBooked[10];
int staffadded = 0;
char staffAdded[10];
int roomsavailable = 9;
char roomsAvailable[10];
char booked[] = "BOOKED";
int iroom_no = atoi(room_no);

/*
	function iDraw() is called again and again by the system.

	*/
int x, y;
void free_string(char *str)
{
	int index = strlen(str);
	while (index != 0)
	{
		str[index - 1] = '\0';
		index--;
	}
}

typedef struct
{
	char name[20];
	char phone[20];
	char roomno[20];
	char check_in[20];
	char check_out[20];
} customers;

customers customer[9];

void readandshowbookinginfo()
{
	FILE *fileptr;

	fileptr = fopen("booking_info.txt", "r");
	if (fileptr == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	int i = 0, y = 501;
	for (i = 0; i < 9; i++)
	{
		fscanf(fileptr, "%19[^,],%19[^,],%19[^,],%19[^,],%19s\n", customer[i].name, customer[i].phone, customer[i].roomno, customer[i].check_in, customer[i].check_out);
		// printf("%s %s %s %s %s", customer[i].name, customer[i].phone, customer[i].roomno, customer[i].check_in, customer[i].check_out);
		iText(24, y, customer[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(245, y, customer[i].phone, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(496, y, customer[i].roomno, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(736, y, customer[i].check_in, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(993, y, customer[i].check_out, GLUT_BITMAP_TIMES_ROMAN_24);
		y -= 30;
	}
	fclose(fileptr);
}

typedef struct
{
	char room_no[20];
} showroombookeds;

showroombookeds showroombooked[9], dummy1[9], dummy[9], dummy2[9], dummy3[9];

void display_room_booked()
{
	FILE *fileptr;

	fileptr = fopen("booking_info.txt", "r");
	if (fileptr == NULL)
	{
		printf("Error opening file!\n");
		return;
	}

	int i = 0, y = 501;
	for (i = 0; i < 9; i++)
	{
		fscanf(fileptr, "%19[^,],%19[^,],%19[^,],%19[^,],%19s\n", dummy1[i].room_no, dummy[i].room_no, showroombooked[i].room_no, dummy2[i].room_no, dummy3[i].room_no);
		printf("%d", atoi(showroombooked[i].room_no));
		// printf("%s %s %s %s %s", customer[i].name, customer[i].phone, customer[i].roomno, customer[i].check_in, customer[i].check_out);
	}
	fclose(fileptr);
}
// int check_booking_info()
// {
// 	FILE *fileptr;
// 	char name[20], phone[20], roomno[20], check_in[20], check_out[20];

// 	fileptr = fopen("booking_info.txt", "r");
// 	if (fileptr == NULL)
// 	{
// 		printf("Error opening file!\n");
// 		return 0;
// 	}

// 	fscanf(fileptr, "%19[^,],%19[^,],%19[^,],%19[^,],%19s\n", name, phone, roomno, check_in, check_out);
// 	if (name[0] == '\0' || phone[0] == '\0' || roomno[0] == '\0' || check_in[0] || '\0' || check_out[0] == '\0')
// 	{
// 		return 0;
// 	}
// 	else
// 		return 1;
// 	// printf("%s %s %s %s %s", customer[i].name, customer[i].phone, customer[i].roomno, customer[i].check_in, customer[i].check_out);

// 	fclose(fileptr);
// }

int verifyadmin(const char *adminID, const char *adminP)
{
	FILE *fileptr;
	char file_adminID[10], file_adminP[10];
	int admin_verified = 0;

	fileptr = fopen("admin_credentials.txt", "r");
	if (fileptr == NULL)
	{
		printf("Error opening file!\n");
		return 0;
	}
	while (fscanf(fileptr, "%[^,], %s\n", file_adminID, file_adminP) == 2)
	{
		if (strcmp(adminID, file_adminID) == 0 && strcmp(adminP, file_adminP) == 0)
		{
			admin_verified = 1;
			break;
		}
	}
	fclose(fileptr);
	return admin_verified;
}

void addbookinginfo(const char *name, const char *phone, const char *room_no, const char *check_in, const char *check_out)
{
	FILE *filePtr;
	char file_name[20], file_phone[20], file_room_no[20], file_check_in[20], file_check_out[20];

	filePtr = fopen("booking_info.txt", "a");
	if (filePtr == NULL)
	{
		printf("Error opening temporary file!\n");
		fclose(filePtr);
		return;
	}
	else
	{
		strcpy(file_name, name);
		strcpy(file_phone, phone);
		strcpy(file_room_no, room_no);
		strcpy(file_check_in, check_in);
		strcpy(file_check_out, check_out);
		fprintf(filePtr, "%s, %s, %s, %s, %s\n", file_name, file_phone, file_room_no, file_check_in, file_check_out);
	}
	fclose(filePtr);
}
void deleteBookingFile()
{
	if (remove("booking_info.txt") == 0)
		printf("File deleted successfully.\n");
	else
		printf("Error deleting file.\n");
}
void deletestaffFile()
{
	if (remove("staff_info.txt") == 0)
		printf("File deleted successfully.\n");
	else
		printf("Error deleting file.\n");
}

typedef struct
{
	char staff_name[20];
	char staff_phone[20];
	char staff_room[20];

} staffs;

staffs staff[9];

void readandshowstaffinfo()
{
	FILE *fileptr;

	fileptr = fopen("staff_info.txt", "r");
	if (fileptr == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	int i = 0, y = 526;
	for (i = 0; i < 9; i++)
	{
		fscanf(fileptr, "%19[^,],%19[^,],%19s\n", staff[i].staff_name, staff[i].staff_phone, staff[i].staff_room);
		// printf("%s %s %s %s %s", customer[i].name, customer[i].phone, customer[i].roomno, customer[i].check_in, customer[i].check_out);
		iText(57, y, staff[i].staff_name, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(536, y, staff[i].staff_phone, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(1030, y, staff[i].staff_room, GLUT_BITMAP_TIMES_ROMAN_24);

		y -= 30;
	}
	fclose(fileptr);
}

void addstaffinfo(const char *staff_name, const char *staff_phone, const char *staff_room)
{
	FILE *filePtr;
	char file_staff_name[20], file_staff_phone[20], file_staff_room_no[20];

	filePtr = fopen("staff_info.txt", "a");
	if (filePtr == NULL)
	{
		printf("Error opening temporary file!\n");
		fclose(filePtr);
		return;
	}
	else
	{
		strcpy(file_staff_name, staff_name);
		strcpy(file_staff_phone, staff_phone);
		strcpy(file_staff_room_no, staff_room);

		fprintf(filePtr, "%s, %s, %s\n", file_staff_name, file_staff_phone, file_staff_room_no);
	}
	fclose(filePtr);
}

void wrongpassword()
{
	iShowBMP(300, 175, "wrongpassword.bmp");
}
void cus()
{
	iShowBMP(0, 0, "contact.bmp");
}

void adminIDTextBox()
{
	iSetColor(0, 0, 0);
	iRectangle(548, 327, 231, 44);
}
void adminPTextBox()
{
	iSetColor(0, 0, 0);
	iRectangle(548, 218, 231, 48);
}

void homescreen()
{
	iShowBMP(0, 0, "Homepage.bmp");
}

void htoaL()
{
	iShowBMP(0, 0, "adminL.bmp");
}
void altoad()
{
	iShowBMP(0, 0, "adminD.bmp");
}
void showbookinginfo()
{
	iShowBMP(0, 0, "sbooking_info.bmp");
}
void aRb()
{
	iShowBMP(0, 0, "aroombookings.bmp");
}
void ats()
{
	iShowBMP(0, 0, "staffpage.bmp");
}
void add_staff()
{
	iShowBMP(0, 0, "addstaff.bmp");
}
void show_staff()
{
	iShowBMP(0, 0, "staff_info.bmp");
}
void staffdone()
{
	iShowBMP(300, 175, "staffaddingdone.bmp");
}
void roomsfb()
{
	iShowBMP(0, 0, "roomsforbooking.bmp");
}
void president()
{
	iShowBMP(0, 0, "president.bmp");
}
void creative()
{
	iShowBMP(0, 0, "creative.bmp");
}
void honeymoon()
{
	iShowBMP(0, 0, "honeymoon.bmp");
}
void delux1()
{
	iShowBMP(0, 0, "deluxe1.bmp");
}
void delux2()
{
	iShowBMP(0, 0, "deluxe2.bmp");
}
void delux3()
{
	iShowBMP(0, 0, "deluxe3.bmp");
}
void bookingpage()
{
	iShowBMP(0, 0, "bookingpage.bmp");
}
void roomnos()
{
	iShowBMP(300, 175, "Roomnos.bmp");
}
void bookingdone()
{
	iShowBMP(150, 88, "bookingdone.bmp");
}
void restaurant()
{
	iShowBMP(0, 0, "restaurant.bmp");
}
void hrooms1()
{
	iShowBMP(0, 0, "rooms1.bmp");
}
void r1rooms2()
{
	iShowBMP(0, 0, "rooms2.bmp");
}

void iDraw()
{
	// place your drawing codes here
	iClear();

	if (home == 0)
	{
		homescreen();
	}

	if (contact == 1 && home == 1)
	{
		cus();
	}
	if (adminL == 1 && home == 1)
	{
		htoaL();
		adminIDTextBox();
		adminPTextBox();
		if (aIDs == 1)
		{
			iSetColor(0, 0, 0);
			iText(553, 340, adminID, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (aPs == 1)
		{
			iSetColor(0, 0, 0);
			iText(553, 228, adminP, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iText(10, 10, "Click to activate the box, enter to finish.");
	}
	if (aLtoaD == 1 && home == 2)
	{
		altoad();
		itoa(roombooked, roomBooked, 10);
		iText(878, 444, roomBooked, GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(roomsavailable, roomsAvailable, 10);
		iText(462, 444, roomsAvailable, GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(staffadded, staffAdded, 10);
		iText(462, 119, staffAdded, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	avr = verifyadmin(adminID, adminP);

	if (wp == 1)
	{
		wrongpassword();
	}
	if (arb == 1 && home == 3)
	{
		aRb();

		for (int i = 0; i < 9; i++)
		{
			int ishowroombooked = atoi(showroombooked[i].room_no);
			if (ishowroombooked == 1)
			{
				iSetColor(0, 0, 0);
				iText(826, 530, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 2)
			{
				iSetColor(0, 0, 0);
				iText(826, 483, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 3)
			{
				iSetColor(0, 0, 0);
				iText(826, 425, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 4)
			{
				iSetColor(0, 0, 0);
				iText(826, 371, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 5)
			{
				iSetColor(0, 0, 0);
				iText(826, 323, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 6)
			{
				iSetColor(0, 0, 0);
				iText(826, 272, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 7)
			{
				iSetColor(0, 0, 0);
				iText(826, 216, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 8)
			{
				iSetColor(0, 0, 0);
				iText(826, 161, booked, GLUT_BITMAP_HELVETICA_18);
			}
			if (ishowroombooked == 9)
			{
				iSetColor(0, 0, 0);
				iText(826, 108, booked, GLUT_BITMAP_HELVETICA_18);
			}
		}

		// int y = 530;
		// for (int i = 0; i < 9; i++)
		// {
		// 	int ishowroombooked = atoi(showroombooked[i].room_no);

		// 	if (ishowroombooked = i + 1)
		// 	{

		// 		iSetColor(0, 0, 0);
		// 		iText(826, y, booked, GLUT_BITMAP_HELVETICA_18);
		// 	}
		// 	y -= 45;
		// }
		// iSetColor(0,0,0);
		// iText(826, 530, booked, GLUT_BITMAP_HELVETICA_18);

		// 	if(iroom_no == 1)
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 530, booked, GLUT_BITMAP_HELVETICA_18);
		// }
		// if(iroom_no == 2)
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 480, booked , GLUT_BITMAP_HELVETICA_18);
		//
		// if(room_no == "3")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 430, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "4")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 380, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "5")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 330, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "6")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 280, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "7")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 230, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "8")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 180, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
		// if(room_no == "9")
		// {
		// 	iSetColor(0,0,0);
		// 	iText(826, 130, "BOOKED", GLUT_BITMAP_HELVETICA_18);
		// }
	}
	if (sbookings == 1 && home == 3)
	{
		showbookinginfo();
		readandshowbookinginfo();
	}
	if (aTs == 1 && home == 3)
	{
		ats();
	}
	if (addstaff == 1)
	{
		add_staff();
		if (stns == 1)
		{
			iSetColor(0, 0, 0);
			iText(280, 469, staff_name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (stphns == 1)
		{
			iSetColor(0, 0, 0);
			iText(280, 316, staff_phone, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (strrms == 1)
		{
			iSetColor(0, 0, 0);
			iText(280, 162, staff_room, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	if (showstaff == 1 && home == 4)
	{
		show_staff();
		readandshowstaffinfo();
	}
	if (addstaffdone == 1 && home == 5)
	{
		// printf("%d",addstaffdone,home);
		staffdone();
		// addstaffinfo(staff_name, staff_phone, staff_phone);
	}

	if (rfb == 1 && home == 1)
	{
		roomsfb();
	}
	// rfb to president
	if (home == 2 && ps == 1)
	{
		president();
	}
	// rfb to creative
	if (home == 2 && cs == 1)
	{
		creative();
	}
	// rfb to honeymoon
	if (home == 2 && hs == 1)
	{
		honeymoon();
	}
	// rfb to d1
	if (home == 2 && d1 == 1)
	{
		delux1();
	}
	// rfb to d2
	if (home == 2 && d2 == 1)
	{
		delux2();
	}
	// rfb to president
	if (home == 2 && d3 == 1)
	{
		delux3();
	}
	if (bpage == 1 && (home == 3 || home == 2))
	{
		bookingpage();
		if (ns == 1)
		{
			iSetColor(0, 0, 0);
			iText(219, 445, name, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (phns == 1)
		{
			iSetColor(0, 0, 0);
			iText(219, 346, phone, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (room_nos == 1)
		{
			iSetColor(0, 0, 0);
			iText(228, 254, room_no, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (checkins == 1)
		{
			iSetColor(0, 0, 0);
			iText(224, 156, check_in, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		if (checkouts == 1)
		{
			iSetColor(0, 0, 0);
			iText(224, 60, check_out, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
	if (rmns == 1 && home == 4)
	{
		roomnos();
		for (int i = 0; i < 9; i++)
		{
			int ishowroombooked = atoi(showroombooked[i].room_no);
			if (ishowroombooked == 1)
			{
				iSetColor(255, 255, 255);
				iText(589, 439, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 2)
			{
				iSetColor(255, 255, 255);
				iText(589, 418, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 3)
			{
				iSetColor(255, 255, 255);
				iText(589, 393, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 4)
			{
				iSetColor(255, 255, 255);
				iText(589, 365, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 5)
			{
				iSetColor(255, 255, 255);
				iText(589, 345, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 6)
			{
				iSetColor(255, 255, 255);
				iText(589, 320, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 7)
			{
				iSetColor(255, 255, 255);
				iText(589, 298, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 8)
			{
				iSetColor(255, 255, 255);
				iText(589, 270, booked, GLUT_BITMAP_HELVETICA_10);
			}
			if (ishowroombooked == 9)
			{
				iSetColor(255, 255, 255);
				iText(589, 247, booked, GLUT_BITMAP_HELVETICA_12);
			}
		}
	}
	if (bdone == 1 && home == 4)
	{
		bookingdone();
		// addbookinginfo(name, phone, room_no, check_in, check_out);
		// printf("%d", iroom_no);
	}
	if (rstrnt == 1 && home == 1)
	{
		restaurant();
	}
	if (r1 == 1 && home == 1)
	{
		hrooms1();
	}
	if (r2 == 1 && home == 2)
	{
		r1rooms2();
	}
	// strcpy(adminID,checkaID);
	// printf("%s", checkaID);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)

{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// adminidtextbox
		if (home == 1 && adminL == 1 && mx >= 548 && mx <= 779 && my >= 329 && my <= 369 && aID == 0)
		{
			aID = 1;
			aIDs = 1;
			aP = 0;
		}
		// admiPtextbox
		if (home == 1 && adminL == 1 && mx >= 548 && mx <= 779 && my >= 218 && my <= 266 && aP == 0)
		{
			aP = 1;
			aPs = 1;
			aID = 0;
		}

		// home to exit
		if (home == 0 && mx >= 98 && mx <= 231 && my >= 40 && my <= 83)
		{
			deleteBookingFile();
			deletestaffFile();
			exit(0);
		}

		// home to contact
		if (home == 0 && mx >= 966 && mx <= 1162 && my >= 241 && my <= 292)
		{

			home = 1;
			contact = 1;
		}
		// back to home
		if (home == 1 && contact == 1 && mx >= 16 && mx <= 112 && my >= 602 && my <= 693)
		{

			home = 0;
			contact = 0;
		}

		// home to rooms

		if (home == 0 && mx >= 966 && mx <= 1162 && my >= 505 && my <= 550)
		{
			r1 = 1;
			home = 1;
		}
		// r1 to bookingpage
		if (home == 1 && r1 == 1 && ((mx >= 90 && mx <= 324 && my >= 185 && my <= 231) || (mx >= 485 && mx <= 715 && my >= 189 && my <= 231) || (mx >= 893 && mx <= 1128 && my >= 183 && my <= 230)))
		{
			bpage = 1;
			home = 2;
		}

		// booking page text boxes
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 213 && mx <= 600 && my >= 436 && my <= 477)
		{
			n = 1, ns = 1, phn = 0, roomno = 0, checkin = 0, checkout = 0;
		}
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 213 && mx <= 600 && my >= 339 && my <= 381)
		{
			n = 0, phns = 1, phn = 1, roomno = 0, checkin = 0, checkout = 0;
		}
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 213 && mx <= 600 && my >= 244 && my <= 282)
		{
			n = 0, room_nos = 1, phn = 0, roomno = 1, checkin = 0, checkout = 0;
		}
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 213 && mx <= 600 && my >= 145 && my <= 188)
		{
			n = 0, checkins = 1, phn = 0, roomno = 0, checkin = 1, checkout = 0;
		}
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 213 && mx <= 600 && my >= 50 && my <= 89)
		{
			n = 0, checkouts = 1, phn = 0, roomno = 0, checkin = 0, checkout = 1;
		}

		// back to r1 er kaj korbo

		// r1 t0 r2
		if (home == 1 && r1 == 1 && mx >= 729 && mx <= 966 && my >= 53 && my <= 119)
		{
			r2 = 1;
			home = 2;
		}
		// //back to home  form r2
		if (home == 2 && r2 == 1 && mx >= 474 && mx <= 728 && my >= 33 && my <= 96)
		{
			home = 0;
		}
		// backfromr1
		if (home == 1 && r1 == 1 && mx >= 244 && mx <= 499 && my >= 49 && my <= 117)
		{
			home = 0;
		}

		// restaurant
		if (home == 0 && mx >= 965 && mx <= 1161 && my >= 377 && my <= 425)
		{
			rstrnt = 1;
			home = 1;
		}
		// backfromrestaurant
		if (rstrnt == 1 && home == 1 && mx >= 500 && mx <= 750 && my >= 42 && my <= 100)
		{

			home = 0;
		}
		/*ADMIN PANEL*/
		/*-----------*/
		// home to rooms for booking
		if (home == 0 && mx >= 428 && mx <= 744 && my >= 488 && my <= 696)
		{
			home = 1;
			rfb = 1;
		}
		// back to home
		if (home == 1 && rfb == 1 && mx >= 23 && mx <= 96 && my >= 611 && my <= 685)
		{
			home = 0;
			rfb = 0;
		}
		// rfb to president
		if (home == 1 && rfb == 1 && mx >= 82 && mx <= 1126 && my >= 469 && my <= 518)
		{
			home = 2;
			ps = 1;
		}
		// rfb to creative
		if (home == 1 && rfb == 1 && mx >= 80 && mx <= 1126 && my >= 417 && my <= 463)
		{
			home = 2;
			cs = 1;
		}
		// rfb to honeymoon
		if (home == 1 && rfb == 1 && mx >= 84 && mx <= 1126 && my >= 360 && my <= 406)
		{
			home = 2;
			hs = 1;
		}
		// rfb to deluxe1
		if (home == 1 && rfb == 1 && mx >= 83 && mx <= 1126 && my >= 253 && my <= 353)
		{
			home = 2;
			d1 = 1;
		}
		// rfb to deluxe2
		if (home == 1 && rfb == 1 && mx >= 83 && mx <= 1126 && my >= 143 && my <= 245)
		{
			home = 2;
			d2 = 1;
		}
		// rfb to deluxe3
		if (home == 1 && rfb == 1 && mx >= 83 && mx <= 1126 && my >= 32 && my <= 130)
		{
			home = 2;
			d3 = 1;
		}
		// rooms to booking page
		if (
			(home == 2 && ps == 1 && mx >= 909 && mx <= 1144 && my >= 354 && my <= 401) ||
			(home == 2 && cs == 1 && mx >= 823 && mx <= 1060 && my >= 353 && my <= 399) ||
			(home == 2 && hs == 1 && mx >= 837 && mx <= 1076 && my >= 412 && my <= 457) ||
			(home == 2 && d1 == 1 && mx >= 847 && mx <= 1084 && my >= 378 && my <= 424) ||
			(home == 2 && d1 == 1 && mx >= 860 && mx <= 1096 && my >= 39 && my <= 82) ||
			(home == 2 && d2 == 1 && mx >= 846 && mx <= 1085 && my >= 377 && my <= 422) ||
			(home == 2 && d2 == 1 && mx >= 862 && mx <= 1097 && my >= 39 && my <= 82) ||
			(home == 2 && d3 == 1 && mx >= 846 && mx <= 1084 && my >= 378 && my <= 422) ||
			(home == 2 && d3 == 1 && mx >= 858 && mx <= 1093 && my >= 42 && my <= 84))
		{
			bpage = 1;
			home = 3;
		}
		// bookingpagetobookingdone
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 808 && mx <= 1125 && my >= 204 && my <= 325)
		{

			bdone = 1;
			home = 4;
			roombooked++;
			roomsavailable--;
		}
		// back to home bookingdone
		if (bdone == 1 && home == 4 && mx >= 556 && mx <= 645 && my >= 116 && my <= 198)
		{
			home = 0;
			addbookinginfo(name, phone, room_no, check_in, check_out);
			// free_string(name);
			// free_string(phone);
			// free_string(room_no);
			// free_string(check_in);
			// free_string(check_out);
		}

		// booking page to room no.s
		if (bpage == 1 && (home == 3 || home == 2) && mx >= 371 && mx <= 597 && my >= 247 && my <= 281)
		{
			rmns = 1;
			home = 4;
			display_room_booked();
		}
		// backfrom roomns
		if (rmns == 1 && home == 4 && mx >= 578 && mx <= 615 && my >= 201 && my <= 217)
		{
			home = 3;
			rmns = 0;
		}
		// back to rfbooking from booking page
		if (bpage == 1 && home == 3 && mx >= 4 && mx <= 152 && my >= 634 && my <= 698)
		{
			home = 1;
			bpage = 0;
			ps = 0, cs = 0, hs = 0, d1 = 0, d2 = 0, d3 = 0;
		}
		// backfrompresident
		if (home == 2 && ps == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			ps = 0;
		}
		// backfromcreative
		if (home == 2 && cs == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			cs = 0;
		}
		// backfromhoneymoon
		if (home == 2 && hs == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			hs = 0;
		}
		// backfromd1
		if (home == 2 && d1 == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			d1 = 0;
		}
		// backfromd2
		if (home == 2 && d2 == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			d2 = 0;
		}
		// backfromd3
		if (home == 2 && d3 == 1 && mx >= 4 && mx <= 188 && my >= 651 && my <= 696)
		{
			home = 1;
			d3 = 0;
		}

		if (mx >= 888 && mx <= 1126 && my >= 653 && my <= 697) // home to adminL
		{
			adminL = 1;
			home = 1;
		}
		if (adminL == 1 && home == 1 && mx >= 3 && mx <= 305 && my >= 634 && my <= 698) // back from adminL
		{

			home = 0;
		}
		if (adminL == 1 && home == 1 && mx >= 449 && mx <= 755 && my >= 36 && my <= 105) // aL to aD
		{
			int admin_verified = verifyadmin(adminID, adminP);
			if (admin_verified)
			{
				aLtoaD = 1;
				home = 2;
			}
			else
			{
				wp = 1;
			}
		}
		// if (avr == 0 && adminL == 1 && home == 1 && mx >= 449 && mx <= 755 && my >= 36 && my <= 105) // aL to aD
		// {
		// 	wp = 1;
		// }
		if (wp == 1 && mx >= 578 && mx <= 624 && my >= 236 && my <= 271)
		{
			home = 0;
		}
		if (aLtoaD == 1 && home == 2 && mx >= 37 && mx <= 231 && my >= 321 && my <= 369) // aD to rooms
		{
			arb = 1;

			home = 3;
			display_room_booked();
		}

		// admin dashboard to show bookings
		if (aLtoaD == 1 && home == 2 && mx >= 41 && mx <= 236 && my >= 439 && my <= 485)
		{
			sbookings = 1;
			home = 3;
			// for (int i = 0; i < 9; i++)
			// {
			// 	iText(24, 501, customer[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
			// }
		}

		// back form showbookings
		if (sbookings == 1 && home == 3 && mx >= 3 && mx <= 152 && my >= 635 && my <= 698)
		{
			sbookings = 0;
			home = 2;
		}

		// back from rooms
		if (arb == 1 && home == 3 && mx >= 4 && mx <= 153 && my >= 633 && my <= 698)
		{

			home = 2;

			arb = 0;
		}
		// aD to staffs
		if (aLtoaD == 1 && home == 2 && mx >= 36 && mx <= 232 && my >= 201 && my <= 251)
		{
			aTs = 1;
			home = 3;
		}

		// staffs to show staff
		if (aTs == 1 && home == 3 && mx >= 445 && mx <= 756 && my >= 259 && my <= 325)
		{
			showstaff = 1;
			home = 4;
		}

		// backfromstaff
		if (showstaff == 1 && home == 4 && mx >= 4 && mx <= 152 && my >= 633 && my <= 698)
		{
			showstaff = 0;
			home = 3;
		}

		// staffs to addstaff
		if (aTs == 1 && home == 3 && mx >= 452 && mx <= 765 && my >= 402 && my <= 467)
		{
			addstaff = 1;
			home = 4;
		}
		/// adding done
		if (addstaff == 1 && home == 4 && mx >= 728 && mx <= 1044 && my >= 219 && my <= 281)
		{
			addstaffdone = 1;
			home = 5;
		}

		// backfrom done
		if (addstaffdone == 1 && home == 5 && mx >= 563 && mx <= 637 && my >= 227 && my <= 258)
		{
			addstaffdone = 0;
			addstaff = 0;
			home = 3;
			addstaffinfo(staff_name, staff_phone, staff_room);
			staffadded++;
			stns = 0;
			stphns = 0;
			strrms = 0;
			free(staff_name);
			free(staff_phone);
			free(staff_room);
		}
		// back from addstaff
		if (addstaff == 1 && home == 4 && mx >= 733 && mx <= 1043 && my >= 132 && my <= 197)
		{
			addstaff = 0;
			home = 3;
		}

		// add staff text boxes
		if (addstaff == 1 && home == 4 && mx >= 256 && mx <= 556 && my >= 457 && my <= 499)
		{
			stns = 1;
			stn = 1;
			stphn = 0;
			strrm = 0;
		}
		if (addstaff == 1 && home == 4 && mx >= 256 && mx <= 556 && my >= 303 && my <= 342)
		{

			stphns = 1;
			stn = 0;
			stphn = 1;
			strrm = 0;
		}
		if (addstaff == 1 && home == 4 && mx >= 256 && mx <= 556 && my >= 149 && my <= 187)
		{

			strrms = 1;
			stn = 0;
			stphn = 0;
			strrm = 1;
		}

		// back from stafss
		if (aTs == 1 && home == 3 && mx >= 4 && mx <= 153 && my >= 635 && my <= 696)
		{

			home = 2;

			aTs = 0;
		}

		if (home == 2 && mx >= 2 && mx <= 197 && my >= 650 && my <= 697) // back to aL from aD
		{

			home = 0;
			aLtoaD = 0;
		}
		if (home == 0)
		{
			adminL = 0;
			home = 0;
			aLtoaD = 0;
			arb = 0;
			aTs = 0;
			rfb = 0;
			ps = 0, cs = 0, hs = 0, d1 = 0, d2 = 0, d3 = 0;
			bpage = 0;
			rmns = 0;
			bdone = 0;
			rstrnt = 0;
			r1 = 0, r2 = 0;
			aP = 0, aID = 0, aPs = 0, aIDs = 0;
			adminID[100] = NULL;

			adminlen = 0;
			passlen = 0;
			adminP[100] = NULL;
			name[100] = NULL, namelen = 0;
			n = 0, ns = 0;
			phone[100] = NULL;
			phn = 0, phns = 0;
			room_no[10] = NULL;
			roomno = 0, room_nos = 0;
			check_in[100] = NULL;
			checkin = 0, checkins = 0;
			check_out[100] = NULL;
			checkout = 0, checkouts = 0;
			wp = 0;

			free_string(adminID);
			free_string(adminP);
		}

		// place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	int i;
	if (aID == 1 && aIDs == 1)
	{
		if (key == '\b' && adminlen > 0)
		{
			adminID[adminlen] = '\0';
			adminlen--;
		}
		else if (key != '\b' && adminlen < 99)
		{
			adminID[adminlen] = key;
			adminlen++;
		}
	}
	if (aP == 1 && aPs == 1)
	{

		if (key == '\b' && passlen > 0)
		{
			adminP[passlen] = '\0';
			passlen--;
		}

		else if (key != '\b' && passlen < 99)
		{
			adminP[passlen] = key;
			passlen++;
		}
	}
	if (n == 1 && ns == 1)
	{

		if (key == '\b' && namelen > 0)
		{
			name[namelen] = '\0';
			namelen--;
		}

		else if (key != '\b' && namelen < 99)
		{
			name[namelen] = key;
			namelen++;
		}
	}
	if (phn == 1 && phns == 1)
	{

		if (key == '\b' && phonelen > 0)
		{
			phone[phonelen] = '\0';
			phonelen--;
		}

		else if (key != '\b' && phonelen < 99)
		{
			phone[phonelen] = key;
			phonelen++;
		}
	}
	if (roomno == 1 && room_nos == 1)
	{

		if (key == '\b' && roomnolen > 0)
		{
			room_no[roomnolen] = '\0';
			roomnolen--;
		}

		else if (key != '\b' && roomnolen < 10)
		{
			room_no[roomnolen] = key;
			roomnolen++;
		}
	}
	if (checkin == 1 && checkins == 1)
	{

		if (key == '\b' && checkinlen > 0)
		{
			check_in[checkinlen] = '\0';
			checkinlen--;
		}

		else if (key != '\b' && checkinlen < 99)
		{

			check_in[checkinlen] = key;
			checkinlen++;
		}
	}
	if (checkout == 1 && checkouts == 1)
	{

		if (key == '\b' && checkoutlen > 0)
		{
			check_out[checkoutlen] = '\0';
			checkoutlen--;
		}

		else if (key != '\b' && checkoutlen < 99)
		{

			check_out[checkoutlen] = key;
			checkoutlen++;
		}
	}
	if (stn == 1 && stns == 1)
	{

		if (key == '\b' && stnlen > 0)
		{
			staff_name[stnlen] = '\0';
			stnlen--;
		}

		else if (key != '\b' && stnlen < 99)
		{

			staff_name[stnlen] = key;
			stnlen++;
		}
	}
	if (stphn == 1 && stphns == 1)
	{

		if (key == '\b' && stphnlen > 0)
		{
			staff_phone[stphnlen] = '\0';
			stphnlen--;
		}

		else if (key != '\b' && stphnlen < 99)
		{

			staff_phone[stphnlen] = key;
			stphnlen++;
		}
	}
	if (strrm == 1 && strrms == 1)
	{

		if (key == '\b' && strrmlen > 0)
		{
			staff_room[strrmlen] = '\0';
			strrmlen--;
		}

		else if (key != '\b' && strrmlen < 99)
		{

			staff_room[strrmlen] = key;
			strrmlen++;
		}
	}

	// place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.

	iInitialize(1200, 700, "Hotel management");
	return 0;
}
