`timescale 1ns / 1ps

module FND_Data(
    input [13:0] i_data,
    input i_clear,
    output [13:0] o_data
    );

    reg [13:0] r_data = 0;
    reg [13:0] r_prev_data = 0;

    assign o_data = r_data;

    always @(*) begin
        if (i_clear) begin
            r_prev_data <= i_data;
        end
        r_data <= i_data - r_prev_data;
    end
endmodule
