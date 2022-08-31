#!/bin/sh
#author Julianus
#Happy hacking

echo "" #cause the file I had had a space at the top

for (( ; ; ))
do
    echo "Enter one of the following actions or press CTRL-D to exit.
C - create a new photo item
R - read an existing photo item
U - update an existing photo item
D - delete an existing photo item
Q - quit"
    read choice
    # echo $choice
    # echo ""

    if [ "$choice" = "c" ] || [ "$choice" = "C" ]; then
        read -p "Enter photo number: " photo_num
        for (( ; ; ))
        do
            if [ $photo_num -ge 1 -a $photo_num -le 99999 ]; then
                break
            fi
            echo "${photo_num} is not in the range 1 to 99999"
            read -p "Enter photo number: " photo_num
        done
        for (( ; ; ))
        do
            read -p "Enter file location: " file_location
            if [ ! -f $file_location ]; then
                echo "ERROR: File ${file_location} does not exist"
            else
                break
            fi
        done
        read -p "Enter year: " year
        for (( ; ; ))
        do
            if [[ "$year" -ge "1950" && "$year" -le "2050" ]]
            then
                break
            fi
            echo "Year ${year} is not in the range 1950 to 2050"
            read -p "Enter year: " year
            if [ "$year" = "" ]; then
                year=1970
            fi
        done
        read -p "Enter month: " month
        for (( ; ; ))
        do
            if [[ "$month" -ge "1" && "$month" -le "12" ]]; then
                break
            fi
            echo "Month ${month} is not in the range 1 to 12"
            read -p "Enter month: " month
        done
        read -p "Enter day: " day
        for (( ; ; ))
        do
            if [ "$day" -ge "1" -a "$day" -le "31" ]; then
                break
            fi
            echo "Day ${day} is not in the range 1 to 31"
            read -p "Enter day: " day
        done
        for (( ; ; ))
        do
            read -p "Enter location: " location
            if [ "$location" != "" ]; then
                break
            fi
            echo "Location must be provided."
        done
        read -p "Enter names (Optional): " names
        
        if [ ! -d "data" ]; then
            echo Creating data directory
            mkdir data
        fi
        touch "data/p${photo_num}.photo"
        echo $file_location >> "data/p${photo_num}.photo"
        echo "${year} ${month} ${day}" >> "data/p${photo_num}.photo"
        echo "${location}" >> "data/p${photo_num}.photo"
        echo "${names}" >> "data/p${photo_num}.photo"
        mod_date=`date "+[%Y-%m-%d %H:%M:%S]"`
        echo "[${mod_date}] CREATED: ${photo_num} - ${file_location} - ${month}/${day}/${year} - ${location} - ${names}" >> ./data/queries.log
        echo "Created data/p${photo_num}.photo"

    elif [ "$choice" == "r" ] || [ "$choice" == "R" ] ; then
        # for (( ; ; ))
        # do
            read -p "Enter photo number: " photo_num
            if test -f "./data/p${photo_num}.photo" ; then
                echo "Photo: ${photo_num}"
                file_location2=`cat "./data/p${photo_num}.photo" | head -n 1`
                echo "File: ${file_location2}"
                year=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 1`
                month=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 2`
                day=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 3`
                echo "Date: ${month}/${day}/${year}"
                location=`cat "./data/p${photo_num}.photo" | head -n 3 | tail -n 1`
                echo "Location: ${location}"
                names=`cat "./data/p${photo_num}.photo" | head -n 4 | tail -n 1`
                echo "Names: ${names}"

                # break
            else
                echo "ERROR: photo p${photo_num}.photo not found"
            fi
        # done
    elif [ "$choice" == "u" ] || [ "$choice" = "U" ]; then
        # for (( ; ; ))
        # do
            read -p "Enter photo number: " photo_num
            file_location=`cat "./data/p${photo_num}.photo" | head -n 1`
            echo "File name is ${file_location}"
            if test -f "./data/p${photo_num}.photo" ; then
                # for (( ; ; ))
                # do
                    # read -p "Enter file location: " file_location
                    # # if [ "$file_location" == "" ]; then
                    # #     file_location=`cat "./data/p${photo_num}.photo" | head -n 1`
                    # #     break
                    # # fi
                    # if [ ! -f $file_location ]; then 
                    #     file_location=`cat "./data/p${photo_num}.photo" | head -n 1`
                    #     # echo "File does not exist. Please try again."
                    # # else
                    # #     break
                    # fi
                # done
                read -p "Enter year: " year
                
                for (( ; ; ))
                do
                    if [ "$year" == "" ]; then
                        year=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 1`
                        echo "Using old year ${year}"
                        break
                    fi
                    if [ "$year" -ge "1950" -a "$year" -le "2050" ]; then
                        break
                    fi
                    echo "Year ${year} is not in the range 1950 to 2050"
                    read -p "Enter year: " year
                done

                read -p "Enter month: " month
                for (( ; ; ))
                do
                    if [ "$month" == "" ]; then
                        month=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 2`
                        echo "Using old month ${month}"
                    fi
                    if [ "$month" -ge "1" -a "$month" -le "12" ]; then
                        break
                    fi
                    echo "Month ${month} is not in the range 1 to 12"
                    read -p "Enter month: " month
                done

                read -p "Enter day: " day
                for (( ; ; ))
                do
                    if [ "$day" == "" ]; then
                        day=`cat "./data/p${photo_num}.photo" | head -n 2 | tail -n 1 | cut -d " " -f 3`
                        echo "Using old day ${day}"
                    fi
                    if [ "$day" -ge "1" -a "$day" -le "31" ]; then
                        break
                    fi
                    echo "Day ${day} is not in the range 1 to 31"
                    read -p "Enter day: " day
                done

                read -p "Enter location: " location
                read -p "Enter names (Optional): " names
                if [ "$location" == "" ]; then
                    location=`cat "./data/p${photo_num}.photo" | head -n 3 | tail -n 1`
                    echo "Using old location ${location}"
                fi
                if [ "$names" == "" ]; then
                    names=`cat "./data/p${photo_num}.photo" | head -n 4 | tail -n 1`
                    echo "Using old names ${names}"
                fi
                echo $file_location > "data/p${photo_num}.photo"
                echo "${year} ${month} ${day}" >> "data/p${photo_num}.photo"
                echo "${location}" >> "data/p${photo_num}.photo"
                echo "${names}" >> "data/p${photo_num}.photo"
                mod_date=`date "+[%Y-%m-%d %H:%M:%S]"`
                echo "[${mod_date}] UPDATED ${photo_num} - ${file_location} - ${month}/${day}/${year} - ${location} - ${names}" >> ./data/queries.log
                # echo "File name is ${file_location}"
                echo "Updated data/p${photo_num}.photo"

            else
                echo "p${photo_num}.photo does not exist"
            fi
        # done
    elif [ "$choice" == "d" ] || [ "$choice" = "D" ]; then
        # for (( ; ; ))
        # do
            read -p "Enter photo number: " photo_num
            if test -f "./data/p${photo_num}.photo" ; then
                rm "./data/p${photo_num}.photo"
                mod_date=`date "+[%Y-%m-%d %H:%M:%S]"`
                echo "[${mod_date}] DELETED ${photo_num}" >> ./data/queries.log
                echo "data/p${photo_num}.photo was successfully deleted."
            else
                echo "ERROR: photo p${photo_num}.photo not found"
            fi
        # done
    elif [ "$choice" == "q" ] || [ "$choice" = "Q" ]; then
        break
    else
        echo "ERROR: invalid option: ${choice}"
    fi
    echo ""
done