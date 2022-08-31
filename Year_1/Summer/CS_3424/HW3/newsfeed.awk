#Author: Julianus

BEGIN {
    swr_acc=0
    swr_rej=0
    swr_can=0
    swr_nam="swrinde"

    new_acc=0
    new_rej=0
    new_can=0
    new_nam="news.cais.net"

    unk_acc=0
    unk_rej=0
    unk_can=0
    unk_nam="?"
}

{
    if (NR == 1) {start_m=$1; start_d=$2; start_t=$3;}

    if ($5 == swr_nam)
    {
        if ($4 == "+" || $4 == "j") 
            swr_acc=swr_acc+1
        else if ($4 == "-") 
            swr_rej=swr_rej+1
        else if ($4 == "c") {
            swr_can=swr_can+1
            swr_acc=swr_acc+1
        }
        else 
            swr_can=swr_can+1
    }
    else if ($5 == new_nam) 
    {
        if ($4 == "+" || $4 == "j") 
            new_acc=new_acc+1
        else if ($4 == "-") 
            new_rej=new_rej+1
        else if ($4 == "c"){
            new_can=new_can+1
            new_acc=new_acc+1
        }
        else 
            new_can=new_can+1
    } 
    else if ($5 == unk_nam) 
    {
        if ($4 == "c"){
            unk_acc=unk_acc+1
            unk_can=unk_can+1
        }
        else if ($4 == "-") 
            unk_rej=unk_rej+1
        else if ($4 == "+" || $4 == "j")
            unk_acc=unk_acc+1

        else 
            unk_can=unk_can+1
    }
}

END { 
    swr_nam="swrinde:"
    new_nam="news.cais.net:"
    unk_nam="?:"
    end_m = $1
    end_d= $2
    end_t=$3
    {printf "%-23sIncoming News Feed Summary\n\n", ""}
    {printf "%-18saccepted%-7srejected%-7scanceled\n", "", "", ""}
    {printf "%-18s%-15s%-15s%-15s\n",swr_nam,swr_acc,swr_rej,swr_can}
    {printf "%-18s%-15s%-15s%-15s\n",new_nam,new_acc,new_rej,new_can}
    {printf "%-18s%-15s%-15s%-15s\n",unk_nam,unk_acc,unk_rej,unk_can} 
    {printf "\n"}
    {printf "Start Time = %s %s %s%-9sEnd Time = %s %s %s", start_m, start_d, start_t, "", end_m, end_d, end_t}
    # {print "\n"} #the file doesn't have an extra line at the end, so I commented this out
}
