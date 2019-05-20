; ModuleID = 'for'
source_filename = "for"

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
  %n = alloca i32, !dbg !8
  store i32 10, i32* %n, !dbg !8
  %sum = alloca i32, !dbg !9
  store i32 0, i32* %sum, !dbg !9
  br label %for.init, !dbg !10

for.init:                                         ; preds = %entry
  %i = alloca i32, !dbg !11
  store i32 0, i32* %i, !dbg !11
  br label %for.cond, !dbg !11

for.cond:                                         ; preds = %for.inc, %for.init
  %0 = load i32, i32* %i, !dbg !12
  %1 = load i32, i32* %n, !dbg !13
  %2 = icmp slt i32 %0, %1, !dbg !12
  br i1 %2, label %for.body, label %for.end, !dbg !12

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %sum, !dbg !14
  %4 = load i32, i32* %i, !dbg !15
  %5 = add i32 %3, %4, !dbg !14
  store i32 %5, i32* %sum, !dbg !16
  br label %for.inc, !dbg !16

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, !dbg !17
  %7 = add i32 %6, 1, !dbg !17
  store i32 %7, i32* %i, !dbg !18
  br label %for.cond, !dbg !18

for.end:                                          ; preds = %for.cond
  ret i32 0
}

attributes #0 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3}

!0 = distinct !DICompileUnit(language: DW_LANG_C, file: !1, producer: "Cheetah Compiler", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2)
!1 = !DIFile(filename: "for.c", directory: "test")
!2 = !{}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 1, type: !5, isLocal: false, isDefinition: true, scopeLine: 1, flags: DIFlagPrototyped, isOptimized: false, unit: !0, retainedNodes: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !DILocation(line: 1, column: 1, scope: !4)
!9 = !DILocation(line: 2, column: 1, scope: !4)
!10 = !DILocation(line: 3, column: 1, scope: !4)
!11 = !DILocation(line: 3, column: 6, scope: !4)
!12 = !DILocation(line: 3, column: 17, scope: !4)
!13 = !DILocation(line: 3, column: 21, scope: !4)
!14 = !DILocation(line: 4, column: 11, scope: !4)
!15 = !DILocation(line: 4, column: 17, scope: !4)
!16 = !DILocation(line: 4, column: 5, scope: !4)
!17 = !DILocation(line: 3, column: 28, scope: !4)
!18 = !DILocation(line: 3, column: 24, scope: !4)
