import sys
import os

# python template.py <directory> <template_file> <date> <output_directory> '<optional_encoding_1>' '<optional_encoding_2>'

if len(sys.argv) < 7: ## If no second encoding is given, then the first one is used
    start_e = "<<"
    end_e = ">>"
else:
    start_e = sys.argv[5]#[1:-1] #commented out since the quotations don't seemed to be passed in
    end_e = sys.argv[6]#[1:-1]

# check directory and template file exist
if not os.path.exists(sys.argv[1]):
    print("Directory does not exist")
    sys.exit()
if not os.path.exists(sys.argv[2]):
    print("Template file does not exist")
    sys.exit()


list_of_files = os.listdir(sys.argv[1])
for file in list_of_files:
    # read file
    with open(sys.argv[1] + "/" + file, "r") as f:
        first_last_name = f.readline().split()
        first_name = first_last_name[0]
        last_name = " ".join(map(str,first_last_name[1:]))
        start_end_data = f.readline().split()
        start_date = start_end_data[0]
        end_date = start_end_data[1]
        balance = f.readline().strip()

        # if output directory does not exist, create it
        if not os.path.exists(sys.argv[4]):
            os.makedirs(sys.argv[4])

        with open(sys.argv[2], "r") as template:
            output_file = "_".join(map(str, last_name.split())) + ".mail"
            with open(sys.argv[4] + "/" + output_file, "w") as output:
                for line in template:
                    if (start_e in line) and (end_e in line):
                        full_line = ""
                        while True:
                            start_index = line.find(start_e)
                            end_index = line.find(end_e)
                            variable = line[start_index + len(start_e):end_index]
                            if variable == "first_name":
                                replace = first_name
                            elif variable == "last_name":
                                replace = last_name
                            elif variable == "lease_start":
                                replace = start_date
                            elif variable == "lease_end":
                                replace = end_date
                            elif variable == "balance":
                                replace = balance
                            elif variable == "apt_number":
                                replace = file[:3]
                            elif variable == "date":
                                replace = sys.argv[3]

                            
                            full_line += line[:start_index] + replace# + line[end_index + len(end_e):]
                            
                            # print(line[end_index + len(end_e):])
                            # print(full_line)
                            # quit()
                            line = line[end_index + len(end_e):]

                            if start_e not in line or end_e not in line:
                                full_line += line
                                print(full_line, end="", file=output)
                                break
                    else:
                        print(line, end="", file=output)
                output.close()
            template.close()
                        
                        
    f.close()
