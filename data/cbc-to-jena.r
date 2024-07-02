
#Working Directory
setwd("/Users/emanuellaude/Downloads");


#CBC-Matrix einlesen
read.cbc<-function(filename, sep="") {
	cbc = read.table(filename, sep=sep, skip=1, stringsAsFactors=F);

	names = cbc[, colnames(cbc) == "V1"];
	cbc = cbc[, colnames(cbc) != "V1"];

	#Leerzeichen löschen
	names = gsub(" ", "", names, fixed=T);

	colnames(cbc)<-names;
	rownames(cbc)<-names;
	return(cbc);
}


adjacency.cbc<-function(cbc, costIns, costDel) {
	adjacency<- apply(cbc, MARGIN=c(1,2), FUN=apply.adjacency.cbc, costIns, costDel);
	return(adjacency);
}

apply.adjacency.cbc<-function(x, costIns, costDel) {
	if(x > 0) {
		return(-costIns);
	} else {
		return(costDel);
	}
}

write.jena<-function(cbc, filenameOutput, costIns, costDel) {
    size=length(cbc[,1]);
    write(size, filenameOutput, 1)
    write(colnames(cbc), filenameOutput, 1, T)
    
    adjacency <-adjacency.cbc(cbc, costIns, costDel)
    

    i=1;
    while(i<=size-1) {
        j=i+1
        l=matrix(NA, 1, size-i);
        while(j<=size) {
            l[j-i]=adjacency[i, j]
            j=j+1;
        }
        write(l, filenameOutput, size-i, T, sep="\t")
        i=i+1
    }
}


#cbc <-read.cbc("scenedescmaceae.cbc.txt", sep="")
#cbc <-read.cbc("fusarium.cbc", sep=",")
#cbc <-read.cbc("placozoa_cbc_matrix", sep="")


#i = 1
#step=0.01
#length = 1 / step
#qs = matrix(NA, 1, length)
#nosols = matrix(NA, 1, length)
#noclusters = matrix(NA, 1, length)
#for(q in seq(from=step, to=1, by=step)) {
#    qs[i]=q
#
#    costIns = length
#    costDel = q*length
#    filenameOutput = paste("data_", i, ".txt", sep="")
#    filenameInput = paste("noSolutions_", i, ".txt", sep="")
#    write.jena(cbc, filenameOutput, costIns, costDel)
#    system(file.path("/Users/emanuellaude/Library/Developer/Xcode/DerivedData/weighted-cluster-editing-gvdbjrkxfpoejteiyocncdvdjlko/Build/Products/Debug/", paste("weighted-cluster-editing -f", filenameOutput, "-v 0 -o", filenameInput, "-O 5")))
#    noSolutions = read.table(filenameInput)[1,1]
#    nosols[i]=noSolutions
#    noclusters[i] =read.table(filenameInput)[2,1]
#    i = i +1
#}
#
#plot(qs, nosols)
#plot(qs, noclusters)

##!/bin/sh
#
#timeout() {
#
#    time=$1
#
#    # start the command in a subshell to avoid problem with pipes
#    # (spawn accepts one command)
#    command="/bin/sh -c \"$2\""
#
#    outputFile=$3
#
#    expect -c "set echo \"-noecho\"; set timeout $time; spawn -noecho $command; expect timeout { exit 1 } eof { exit 0 }"
#
#    if [ $? = 1 ] ; then
#    echo "timeout" > $outputFile
#    fi
#
#}
#
#timeout $1 "/Users/emanuellaude/Library/Developer/Xcode/DerivedData/weighted-cluster-editing-gvdbjrkxfpoejteiyocncdvdjlko/Build/Products/Debug/weighted-cluster-editing -f $2 -v 0 -o $3 -O 5 -n 1 -m 10" $3

files = list.files(pattern="cm$", path="/Users/emanuellaude/Downloads/runtime-analysis/weighted")
for(file in files) {
    print(file)
    system(paste("sh runtime.sh 600 runtime-analysis/weighted/", file, " ", "runtime-analysis/weighted/", file, "_output.txt", sep=""))
}



files = list.files(pattern="txt$", path="/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution2")
x = matrix(NA, 1, 20);
y = matrix(NA, 1, 20);
i = 1
for(file in files) {
    tab = read.table(paste("/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution2/", file, sep=""));
    if(tab[1,1]=="timeout") {
        
        noNode = sub(".*?_size_([0-9]+).*", "\\1", file,perl=TRUE)
        x[i]=noNode
        y[i]=600
        i = i+1
        next
    }
    noNodes = tab[5,2]
    overallTime = tab[3,2]
    print(overallTime)
    x[i] = noNodes
    y[i] = overallTime
    i= i+1
}
plot(x,y, main="Gesamtlaufzeit in Abhängikeit von der Instanzgröße (Timeout: 600 s)", xlab="Anzahl der Knoten (logarithmisch skaliert)", ylab="Gesamtlaufzeit in Sekunden (logarithmisch skaliert)", log="xy")
abline(h = 600, col = "red")
text(10,600, "Timeout", col = "red", adj=c(0,-0.1))

files = list.files(pattern="txt$", path="/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3")
x = matrix(NA, 1, 20);
y = matrix(NA, 1, 20);
i = 1
for(file in files) {
    tab = read.table(paste("/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3/", file, sep=""));
    if(tab[1,1]=="timeout") {
        next
    }
    k = tab[1,2]
    
    noDeletions = tab[2,2]
    costDeletions = tab[3,2]
    noInsertions = tab[4,2]
    costInsertions = tab[5,2]
    noClusters = tab[6,2]
    nodesAfterReduction = tab[7,2]
    nodesBeforeReduction = tab[8,2]
    edgesBeforeReduction = tab[9,2]
    ilpTime = tab[10,2]
    reductionTime = tab[11,2]
    overallTime = tab[12,2]

    reductionQuality = 1 - nodesAfterReduction / nodesBeforeReduction
    noEdits = noDeletions + noInsertions

    print(k)
    x[i] = k
    y[i] = reductionQuality
    i= i+1
}
plot(x,y, main="Gesamtlaufzeit (Reduktion + ILP) in Abhängikeit des Reduktionsfaktors", xlab="Reduktionsfaktor", ylab="Gesamtlaufzeit in Sekunden")

plot(x,y, main="Reduktionsfaktor in Abhängikeit der Instanzgröße", xlab="Anzahl der Knoten", ylab="Reduktionsfaktor")

files = list.files(pattern="txt$", path="/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3")
for(i in 0:50) {
    lower = i*10 +1
    higher = (i+1)*10

    edits = matrix(NA, 1, 20);
    costs = matrix(NA, 1, 20);
    noNodes = matrix(NA, 1, 20);

    noNodesReduced = matrix(NA, 1, 20);
    noEdges = matrix(NA, 1, 20);
    times = matrix(NA, 1, 20);
    timeouts = matrix(0, 1, 20);
    
    j = 1
    for(file in files) {
        tab = read.table(paste("/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3/", file, sep=""));
        if(tab[1,1]=="timeout") {
            noNode = as.numeric(sub(".*?_size_([0-9]+).*", "\\1", file,perl=TRUE))

            if(noNode < lower) {
                next
            }
            
            if(noNode > higher) {
                next
            }

            edits[j] = NA
            costs[j] = NA
            noNodes[j] = noNode
            noNodesReduced[j] = NA
            noEdges[j] = NA
            times[j] = NA
            timeouts[j] = 1

            j = j+1
            next
        }
        k = tab[1,2]
        noDeletions = tab[2,2]
        costDeletions = tab[3,2]
        noInsertions = tab[4,2]
        costInsertions = tab[5,2]
        noClusters = tab[6,2]
        nodesAfterReduction = tab[7,2]
        nodesBeforeReduction = tab[8,2]
        if(nodesBeforeReduction < lower) {
            next
        }
        if(nodesBeforeReduction > higher) {
            next
        }
        edgesBeforeReduction = tab[9,2]
        ilpTime = tab[10,2]
        reductionTime = tab[11,2]
        overallTime = tab[12,2]
        reductionQuality = 1 - nodesAfterReduction / nodesBeforeReduction
        noEdits = noDeletions + noInsertions

        edits[j] = noEdits
        costs[j] = k
        noNodes[j] = nodesBeforeReduction
        noNodesReduced[j] = nodesAfterReduction
        noEdges[j] = edgesBeforeReduction
        times[j] = overallTime
        timeouts[j] = 0

        j= j+1
    }
    
    edit = round(mean(edits[!is.na(edits)]))
    minNodes = min(noNodes[!is.na(noNodes)])
    minEdges = min(noEdges[!is.na(noEdges)])
    maxEdges = max(noEdges[!is.na(noEdges)])
    count = length(noNodes[!is.na(noNodes)])
    maxNodes = max(noNodes[!is.na(noNodes)])
    reduced = round(mean(noNodesReduced[!is.na(noNodesReduced)]))
    costs = round(mean(costs[!is.na(costs)]), 1)
    runtime = round(mean(times[!is.na(times)]), 3)
    to = sum(timeouts)

    print(paste("$", minNodes, "$-$", maxNodes, "$ & $", count, "$ & $", edit, "$ & $", costs, "$ & $", reduced, "$ & $", runtime, "$ & $", to, "$ \\", sep=""))
}

files = list.files(pattern="txt\n$", path="/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3")
for(file in files) {
    file.rename(paste("/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3/", file, sep=""), paste("/Users/emanuellaude/Downloads/runtime-analysis/weighted/solution3/", gsub("_output.txt\n", "", file), sep=""))
}