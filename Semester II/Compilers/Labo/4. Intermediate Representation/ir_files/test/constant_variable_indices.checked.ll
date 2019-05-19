; ModuleID = 'test/constant_variable_indices.checked.bc'
source_filename = "constant_variable_indices"

@format = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@format.1 = private unnamed_addr constant [3 x i8] c"%d\00"

declare i32 @printf(i8*, ...)

define internal void @echo(i32) {
entry:
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @format, i32 0, i32 0), i32 %0)
  ret void
}

declare i32 @scanf(i8*, ...)

define internal i32 @read() {
entry:
  %toScan = alloca i32
  %0 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @format.1, i32 0, i32 0), i32* %toScan)
  %1 = load i32, i32* %toScan
  ret i32 %1
}

declare i32 @rand()

; Function Attrs: nounwind
define dso_local i32 @main() #0 !dbg !4 {
entry:
  %foo = alloca [10 x i32], !dbg !8
  %a = alloca i32, !dbg !9
  store i32 0, i32* %a, !dbg !9
  %b = alloca i32, !dbg !10
  store i32 9, i32* %b, !dbg !10
  %c = alloca i32, !dbg !11
  store i32 10, i32* %c, !dbg !11
  %0 = load i32, i32* %a, !dbg !12
  %1 = alloca i32, !dbg !12
  store i32 10, i32* %1, !dbg !12
  %2 = load i32, i32* %1, !dbg !12
  %3 = icmp sge i32 %0, %2, !dbg !12
  br i1 %3, label %trap, label %cont, !dbg !12

cont:                                             ; preds = %entry
  %4 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %0, !dbg !12
  store i32 1, i32* %4, !dbg !13
  %5 = load i32, i32* %a, !dbg !14
  %6 = alloca i32, !dbg !14
  store i32 10, i32* %6, !dbg !14
  %7 = load i32, i32* %6, !dbg !14
  %8 = icmp sge i32 %5, %7, !dbg !14
  br i1 %8, label %trap2, label %cont1, !dbg !14

cont1:                                            ; preds = %cont
  %9 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %5, !dbg !14
  %10 = load i32, i32* %9, !dbg !15
  call void @echo(i32 %10), !dbg !15
  %11 = load i32, i32* %b, !dbg !16
  %12 = alloca i32, !dbg !16
  store i32 10, i32* %12, !dbg !16
  %13 = load i32, i32* %12, !dbg !16
  %14 = icmp sge i32 %11, %13, !dbg !16
  br i1 %14, label %trap4, label %cont3, !dbg !16

cont3:                                            ; preds = %cont1
  %15 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %11, !dbg !16
  store i32 1, i32* %15, !dbg !17
  %16 = load i32, i32* %b, !dbg !18
  %17 = alloca i32, !dbg !18
  store i32 10, i32* %17, !dbg !18
  %18 = load i32, i32* %17, !dbg !18
  %19 = icmp sge i32 %16, %18, !dbg !18
  br i1 %19, label %trap6, label %cont5, !dbg !18

cont5:                                            ; preds = %cont3
  %20 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %16, !dbg !18
  %21 = load i32, i32* %20, !dbg !19
  call void @echo(i32 %21), !dbg !19
  %22 = load i32, i32* %c, !dbg !20
  %23 = alloca i32, !dbg !20
  store i32 10, i32* %23, !dbg !20
  %24 = load i32, i32* %23, !dbg !20
  %25 = icmp sge i32 %22, %24, !dbg !20
  br i1 %25, label %trap8, label %cont7, !dbg !20

cont7:                                            ; preds = %cont5
  %26 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %22, !dbg !20
  store i32 1, i32* %26, !dbg !21
  %27 = load i32, i32* %c, !dbg !22
  %28 = alloca i32, !dbg !22
  store i32 10, i32* %28, !dbg !22
  %29 = load i32, i32* %28, !dbg !22
  %30 = icmp sge i32 %27, %29, !dbg !22
  br i1 %30, label %trap10, label %cont9, !dbg !22

cont9:                                            ; preds = %cont7
  %31 = getelementptr [10 x i32], [10 x i32]* %foo, i32 0, i32 %27, !dbg !22
  %32 = load i32, i32* %31, !dbg !23
  call void @echo(i32 %32), !dbg !23
  ret i32 0

trap:                                             ; preds = %entry
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 5)
  unreachable

trap2:                                            ; preds = %cont
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 6)
  unreachable

trap4:                                            ; preds = %cont1
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 7)
  unreachable

trap6:                                            ; preds = %cont3
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 8)
  unreachable

trap8:                                            ; preds = %cont5
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 9)
  unreachable

trap10:                                           ; preds = %cont7
  call void (i8*, i8*, i32, ...) @__assert(i8* null, i8* null, i32 10)
  unreachable
}

; Function Attrs: noreturn
declare void @__assert(i8*, i8*, i32, ...) #1

attributes #0 = { nounwind }
attributes #1 = { noreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "constant_variable_indices.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 1, column: 1, scope: !4)
!9 = !DILocation(line: 2, column: 1, scope: !4)
!10 = !DILocation(line: 3, column: 1, scope: !4)
!11 = !DILocation(line: 4, column: 1, scope: !4)
!12 = !DILocation(line: 5, column: 5, scope: !4)
!13 = !DILocation(line: 5, column: 1, scope: !4)
!14 = !DILocation(line: 6, column: 10, scope: !4)
!15 = !DILocation(line: 6, column: 6, scope: !4)
!16 = !DILocation(line: 7, column: 5, scope: !4)
!17 = !DILocation(line: 7, column: 1, scope: !4)
!18 = !DILocation(line: 8, column: 10, scope: !4)
!19 = !DILocation(line: 8, column: 6, scope: !4)
!20 = !DILocation(line: 9, column: 5, scope: !4)
!21 = !DILocation(line: 9, column: 1, scope: !4)
!22 = !DILocation(line: 10, column: 10, scope: !4)
!23 = !DILocation(line: 10, column: 6, scope: !4)
