#include <iostream>
#include <ilcplex/ilocplex.h>

int main() {
    IloEnv env;

    // Construct the model
    IloModel model(env);

    IloNumVarArray x(env);
    IloRangeArray con(env);
    x.add(IloNumVar(env, 0.0, 40.0));
    x.add(IloNumVar(env));
    x.add(IloNumVar(env));

    model.add(IloMaximize(env, x[0] + 2 * x[1] + 3 * x[2]));

    con.add(-x[0] + x[1] + x[2] <= 20);
    con.add(x[0] - 3 * x[1] + x[2] <= 30);

    x[0].setName("x1");
    x[1].setName("x2");
    x[2].setName("x3");

    con[0].setName("c1");
    con[1].setName("c2");
    model.add(con);
    IloCplex cplex(model);
    cplex.exportModel("model.lp");


    // Optimize the problem and obtain solution.
    if (!cplex.solve()) {
        env.error() << "Failed to optimize LP" << std::endl;
        throw std::runtime_error("Failed to optimize LP");
    }

    IloNumArray vals(env);
    env.out() << "Solution status = " << cplex.getStatus() << std::endl;
    env.out() << "Solution value  = " << cplex.getObjValue() << std::endl;
    cplex.getValues(vals, x);
    env.out() << "Values        = " << vals << std::endl;
    cplex.getSlacks(vals, con);
    env.out() << "Slacks        = " << vals << std::endl;
    cplex.getDuals(vals, con);
    env.out() << "Duals         = " << vals << std::endl;
    cplex.getReducedCosts(vals, x);
    env.out() << "Reduced Costs = " << vals << std::endl;

    return EXIT_SUCCESS;
}
