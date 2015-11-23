#include "main.hh"

RcppExport SEXP solo(const SEXP R_data, const SEXP R_map_settings) {

    // SEXP R types
    NumericMatrix data_input(R_data);
    List settings(R_map_settings);

    Matrix2Df dataset;
    Matrix3Df sofm_weights;

    int nodes, nvars, ndata, niter, nodes_p2;
    float width;

    // create a SOFM object
    SOFM som;

    // assign settings for SOFM
    nvars = data_input.ncol();
    ndata = data_input.nrow();
    nodes = settings["nodes"];
    niter = settings["iter"];
    width = settings["width"];

    nodes_p2 = pow(nodes, 2);

    // create SEXP output object
    NumericMatrix sofm_output(nodes_p2, nvars);

    // set C matrix sizes
    alloc_Mat2D(ndata, nvars, dataset);
    alloc_Mat3D(nodes, nodes, nvars, sofm_weights);


    // transfer data in SEXP object to STL vector
    for(int i=0; i<ndata; i++) {
        for(int j=0; j<nvars; j++) {
            dataset[i][j] = data_input(i, j);
    }}

    printf("Creating a [%d x %d] size SOFM map for %d covariates\n", nodes, nodes, nvars);
    printf("\nProgress:\n")
    // clusters dataset values into nodes and returns a weighted location map
    // of each instantaneous set of values in datasets
    som.predict_map(dataset, nodes, nvars, ndata, niter, width, sofm_weights);
    printf("\n\n");

//    for(int i=0; i<nodes; i++)
//        for(int j=0; j<nodes; j++)
//            for(int k=0; k<nvars; k++)
//                cout << sofm_weights[i][j][k] << endl;

    // return back to R
    return List::create(_("weights") = sofm_weights);

}
