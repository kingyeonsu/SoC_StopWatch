`timescale 1ns / 1ps

module MUX4(
    input [3:0] i_1000, i_100, i_10, i_1,
    input [1:0] i_counter,

    output [3:0] o_data
    );

    reg [3:0] r_data;
    assign o_data = r_data;

    always @(*) begin
        case (i_counter)    
            2'b00: r_data = i_1;
            2'b01: r_data = i_10;
            2'b10: r_data = i_100;
            2'b11: r_data = i_1000;
        endcase
        
    end     

endmodule
