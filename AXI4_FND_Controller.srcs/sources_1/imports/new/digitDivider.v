`timescale 1ns / 1ps

module digitDivider(
    input [13:0] i_value,
    
    output [3:0] o_1000, o_100, o_10, o_1
    );

    assign o_1      = i_value % 10;
    assign o_10     = i_value / 10 % 10;
    assign o_100    = i_value / 100 % 10;
    assign o_1000   = i_value /1000 % 10;

endmodule
