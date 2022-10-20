`timescale 1ns / 1ps

module FND_Controller(
    input i_clk,
    input i_reset,
    input [13:0] i_data,
    input [1:0] i_control,
    
    output [3:0] o_fndPosition,
    output [7:0] o_fndData
    );

    wire w_clk_1k;
    wire [1:0] w_counter;
    wire [13:0] w_value;
    wire [3:0] w_1, w_10, w_100, w_1000, w_data;

    ClockDivider U0(
        .i_clk(i_clk),
        .i_reset(i_reset),
        .o_clk(w_clk_1k)
    );

    counterFND U1(
        .i_clk_1k(w_clk_1k),
        .i_reset(i_reset),
        .o_counter(w_counter)
    );

    decoder2x4 U2(
        .i_counter(w_counter),
        .o_fndDigit(o_fndPosition)
    );

    FND_Data U3(
        .i_data(i_data),
        .i_clear(i_control[0]),
        .o_data(w_value)
    );

    digitDivider U4(
        .i_value(w_value),
        .o_1(w_1),
        .o_10(w_10),
        .o_100(w_100),
        .o_1000(w_1000)
    );

    MUX4 U5(
        .i_1(w_1),
        .i_10(w_10),
        .i_100(w_100),
        .i_1000(w_1000),
        .i_counter(w_counter),
        .o_data(w_data)
    );

    BCDtoFNDdecoder U6(
        .i_data(w_data),
        .i_on_off(i_control[1]),
        .o_fndData(o_fndData)
    );

endmodule
