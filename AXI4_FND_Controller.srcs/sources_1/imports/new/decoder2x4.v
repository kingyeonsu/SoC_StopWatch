`timescale 1ns / 1ps

module decoder2x4(
    input [1:0] i_counter,
    
    output [3:0] o_fndDigit
    );

    reg [3:0] r_fndDigit;
    assign o_fndDigit = r_fndDigit;

    always @(*) begin
        case (i_counter)
            2'b00 : r_fndDigit = 4'b1110;
            2'b01 : r_fndDigit = 4'b1101;
            2'b10 : r_fndDigit = 4'b1011;
            2'b11 : r_fndDigit = 4'b0111;
            default : r_fndDigit = 4'b1111;
        endcase
    end
endmodule
