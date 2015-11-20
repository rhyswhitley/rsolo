#!/usr/bin/env Rscript

library(solo)

# practice dataset
data(iris)

# normalised data for sofm
inputs <- apply(iris[1:4], 2, 
                function(x) (x-min(x))/(max(x)-min(x)))

cat("nvar is: ", ncol(inputs), "\n")
cat("ndata is: ", nrow(inputs), "\n")
#write.table(inputs, file="~/Repositories/R_packages/rsolo/test_scripts/datatest.txt", 
#            row.names=F, col.names=F, sep="\t")

# test sofm
xnode <- 2
xnvar <- ncol(inputs)
outmap <- solo(inputs, xnode, 2000)

print(outmap$weights)


message("\nme down here\n")
#p1 <- vector(mode="list", length=xnode)
for(i in 1:length(xnode)) {
    for(j in 1:length(xnvar)) {
        tmp <- outmap$weights[[i]][[j]] 
        print(tmp)
        #p1[[i]] <- t(matrix(rapply(tmp, rbind), ncol(inputs), xnode))
    }
}

