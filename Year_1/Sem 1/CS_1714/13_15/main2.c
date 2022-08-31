#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	int pass_digit = 0;
	int pw_length = 3;
	int i;
	int secondary_digit = 0;
	int counter = 0;
	int possibilities = 0;

	char char1, char2, char3;
	char secondary_char = '0';

	printf("\n.......:::Testing Password Possibility Generator:::........\n");
	printf("Specify Password Length (Max. 3):");
	scanf("%d",&pw_length);

	while (pw_length > 3)
	{
		printf("\nInvalid Length.\n");
		printf("Try again:");
		scanf("%d",&pw_length);
	}

	char pw[pw_length];

//	Loop to initialize the password string
//==========================================================================
	for (i = 0; i < pw_length; i++)
	{
		pw[i] = 0;
		
		if (i + 1 == pw_length)
			pw[i + 1] = '\0';
	}
//==========================================================================

	FILE * fstream;
	fstream = fopen("combos.txt", "w+");


	for (char1 = '0'; char1 <= 'z' ; char1++)
	{
		pw[pass_digit] = char1;
		fprintf(fstream,"%s\n", pw);

		if (char1 == '9')
			char1 = char1 + 7;

		if (char1 == 'Z')
			char1 = char1 + 6;

	}

	pass_digit++;

	if(pass_digit < pw_length)
	{

		for (char1 = '0'; char1 <= 'z' ; char1++)
		{
			pw[pass_digit-1] = char1;

			if (char1 == '9')
				char1 = char1 + 7;

			if (char1 == 'Z')
				char1 = char1 + 6;
			
			for (char2 = '0'; char2 <= 'z' ; char2++)
			{
				pw[pass_digit] = char2;
				fprintf(fstream,"%s\n",pw);

				if (char2 == '9')
					char2 = char2 + 7;

				if (char2 == 'Z')
					char2 = char2 + 6;
			}
		}

		pass_digit++;

		if (pass_digit < pw_length)
		{
			for (char1 = '0'; char1 <= 'z' ; char1++)
			{
				pw[pass_digit-2] = char1;

				if (char1 == '9')
					char1 = char1 + 7;

				if (char1 == 'Z')
					char1 = char1 + 6;
			
				for (char2 = '0'; char2 <= 'z' ; char2++)
				{
					pw[pass_digit-1] = char2;
					fprintf(fstream,"%s\n",pw);

					if (char2 == '9')
						char2 = char2 + 7;

					if (char2 == 'Z')
						char2 = char2 + 6;

					for (char3 = '0'; char3 <= 'z' ; char3++)
					{
						pw[pass_digit] = char3;
						fprintf(fstream,"%s\n",pw);

						if (char3 == '9')
							char3 = char3 + 7;

						if (char3 == 'Z')
							char3 = char3 + 6;
					}
				}
			}
		}
	}

	printf("Its done! Check the combos.txt\n\n");

	fclose(fstream);

	return 1;
}