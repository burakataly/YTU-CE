module testbench();
    reg clk;
    reg reset;
    wire [31:0] WriteData, DataAdr;
    wire MemWrite;

    top uut (
        .clk(clk), 
        .reset(reset), 
        .WriteData(WriteData), 
        .DataAdr(DataAdr), 
        .MemWrite(MemWrite)
    );

    initial begin
        reset <= 1;
        #22; 
        reset <= 0;
    end

    always begin
        clk <= 1; 
        #5; 
        clk <= 0; 
        #5;
    end

    integer i = 0;

    parameter ARR_LENGTH = 20;


    // Check results and display progress
    always @(negedge clk) begin
        $display("At time %t: DataAdr = %0d, WriteData = %0d, MemWrite = %0b", $time, DataAdr, WriteData, MemWrite);
        if (MemWrite) begin
            i = i + 1;
            $display("Memory Write: Address = %0d, Data = %0d", DataAdr, WriteData);
        end
        
        if (i >= ARR_LENGTH) begin
            $display("Simulation succeeded after %0d iterations", ARR_LENGTH);
            $finish;
        end
    end


    initial begin
        $dumpfile("riscvtest.vcd"); 
        $dumpvars(0, testbench);
    end
endmodule

//iverilog -o riscvtest top.v riscvsingle.v controller.v maindec.v aludec.v datapath.v adder.v extend.v flopr.v flopenr.v mux2.v mux3.v alu.v imem.v regfile.v dmem.v testbench.v
//vvp riscvtest