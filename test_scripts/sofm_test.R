#!/usr/bin/env Rscript

library(solo)
library(lattice)

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
nodes <- 10
nvars <- ncol(inputs)
system.time(sofm.out <- solo(inputs, nodes, 1e5))

quartz()
levelplot(sofm.out$soms[[1]])

# COMPARE SPEED TO KOHONEN PACKAGE

# Change the data frame with training data to a matrix
# Also center and scale all variables to give them equal importance during
# the SOM training process. 
data_train_matrix <- as.matrix(scale(iris[,1:4]))

# Create the SOM Grid - you generally have to specify the size of the 
# training grid prior to training the SOM. Hexagonal and Circular 
# topologies are possible
som_grid <- somgrid(xdim=nodes, ydim=nodes, topo="rectangular")

# Finally, train the SOM, options for the number of iterations,
# the learning rates, and the neighbourhood are available
system.time(
som_model <- som(data_train_matrix, 
                    grid=som_grid, 
                    rlen=1e5, 
                    alpha=c(0.05,0.01), 
                    keep.data=TRUE, 
                    n.hood="square")
)
