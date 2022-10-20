`timescale 1ns / 1ps

module BCDtoFNDdecoder(
    input [3:0] i_data,
    input i_on_off,

    output [7:0] o_fndData
    );

    reg [7:0] r_fndData;
    assign o_fndData = r_fndData;

    always @(*) begin
        if (i_on_off) begin
            r_fndData = 8'hff;  
        end
        else begin
            case (i_data)
                4'h0 : r_fndData = 8'hc0;
                4'h1 : r_fndData = 8'hf9;
                4'h2 : r_fndData = 8'ha4;
                4'h3 : r_fndData = 8'hb0;
                4'h4 : r_fndData = 8'h99;
                4'h5 : r_fndData = 8'h92;
                4'h6 : r_fndData = 8'h82;
                4'h7 : r_fndData = 8'hf8;
                4'h8 : r_fndData = 8'h80;
                4'h9 : r_fndData = 8'h90;
                4'ha : r_fndData = 8'h7f; 
                default: r_fndData = 8'hff;  
            endcase
        end       
    end

endmodule
