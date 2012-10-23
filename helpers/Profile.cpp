/* -----------------------------------------------------------------------------

	Copyright (c) 2012 Niels Fröhling              niels@paradice-insight.us

	Permission is hereby granted, free of charge, to any person obtaining
	a copy of this software and associated documentation files (the
	"Software"), to	deal in the Software without restriction, including
	without limitation the rights to use, copy, modify, merge, publish,
	distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to
	the following conditions:

	The above copyright notice and this permission notice shall be included
	in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
	CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

   -------------------------------------------------------------------------- */

#include "../SolveTSP.h"
#include "Profile.h"

#if	defined(AMP_PROFILE)
#ifdef	_WIN64
#pragma comment(lib, "../../helpers/gpuperf/Bin/x64/GPUPerfAPIDX11-x64.lib")
#else
#pragma comment(lib, "../../helpers/gpuperf/Bin/x86/GPUPerfAPIDX11.lib")
#endif

const char *EnableCounters[] = {
    // Timing
//  "CSBusy",			// The percentage of time the ShaderUnit has compute shader work to do.	7xxx
    "GPUTime",			// Time, in milliseconds, this API call took to execute on the GPU. Does not include time that draw calls are processed in parallel.
    "GPUBusy",			// The percentage of time GPU was busy
    "ShaderBusy",		// The percentage of GPUTime that the shader unit is busy.
    "ShaderBusyCS",		// The percentage of work done by shader units for CS.
    "TexUnitBusy",		// Percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.

    // TextureUnit
    "TexCacheStalled",		// Percentage of GPUTime the texture cache is stalled. Try reducing the number of textures or reducing the number of bits per pixel (use compressed textures), if possible.
    "TexelFetchCount",		// The total number of texels fetched. This includes all shader types, and any extra fetches caused by trilinear filtering, anisotropic filtering, color formats, and volume textures.
    "TexMemBytesRead",		// Texture memory read in bytes.
    "TexMissRate",		// Texture cache miss rate (bytes/texel). A normal value for mipmapped textures on typical scenes is approximately (texture_bpp / 4). For 1:1 mapping, it is texture_bpp.

    // TextureFormat
    "Pct64SlowTexels",		// Percentage of texture fetches from a 64-bit texture (slow path). There are also 64-bit formats that take a fast path; they are included in PctUncompressedTexels.
    "Pct128SlowTexels",		// Percentage of texture fetches from a 128-bit texture (slow path). There also are 128-bit formats that take a fast path; they are included in PctUncompressedTexels.
    "PctTex1D",			// Percentage of texture fetches from a 1D texture.
    "PctTex1DArray",		// Percentage of texture fetches from a 1D texture.
    "PctTex2D",			// Percentage of texture fetches from a 2D texture.
    "PctTex2DArray",		// Percentage of texture fetches from a 1D texture.
    "PctUncompressedTexels",	// Percentage of texture fetches from uncompressed textures. Does not include depth or interlaced textures.

    // ComputeShader
    "CSALUBusy",		// The percentage of GPU Time ALU instructions are processed by the CS.
    "CSALUFetchRatio",		// The ratio of ALU to fetch instructions. This can be tuned to match the target hardware.
    "CSALUInsts",		// The number of ALU instructions executed in the CS. Affected by the flow control.
    "CSALUPacking",		// ALU vector packing efficiency. Values below 70 percent indicate that ALU dependency chains may prevent full use of the processor.
    "CSALUStalledByLDS",	// The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).
    "CSCacheHit",		// The percentage of fetches from the global memory that hit the texture cache.
    "CSCompletePath",		// The total bytes read and written through the CompletePath. This includes extra bytes needed for addressing, atomics, etc. This number indicates a big performance impact (higher number equals lower performance). Reduce it by removing atomics and non 32-bit types, or move them into a second shader.
    "CSFastPath",		// The total bytes written through the FastPath (no atomics, 32-bit type only). This includes extra bytes needed for addressing.
    "CSFetchInsts",		// Average number of fetch instructions executed in the CS per execution. Affected by the flow control.
//  "CSFetchSize",		// The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account. 7xxx
//  "CSGDSInsts",		// The average number of instructions to/from the GDS executed per work-item (affected by flow control). This counter is a subset of the VALUInsts counter. 7xxx
    "CSLDSBankConflict",	// The percentage of GPUTime the LDS is stalled by bank conflicts.
//  "CSLDSBankConflictAccess",	// The percentage of LDS accesses that caused a bank conflict. ????
    "CSLDSFetchInsts",		// The average number of LDS fetch instructions executed per work-item (affected by flow control). This counter is a subset of the VALUInsts counter.
    "CSLDSWriteInsts",		// The average number of LDS write instructions executed per work-item (affected by flow control). This counter is a subset of the VALUInsts counter.
//  "CSMemUnitBusy",		// The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound). 7xxx
//  "CSMemUnitStalled",		// The percentage of GPUTime the memory unit is stalled. Try reduce the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad). 7xxx
    "CSPathUtilization",	// The percentage of bytes read and written through the FastPath or CompletePath compared to the total number of bytes transferred over the bus. To increase the path utilization, remove atomics and non 32-bit types.
//  "CSSALUBusy",		// The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal). 7xxx
//  "CSSALUInsts",		// The average number of scalar ALU instructions executed per work-item (affected by flow control). 7xxx
//  "CSSFetchInsts",		// The average number of scalar fetch instructions from the video memory executed per work-item (affected by flowcontrol). 7xxx
    "CSTexBusy",		// The percentage of GPUTime texture instructions are processed by the CS.
//  "CSThreadGroups",		// Total number of thread groups. 7xxx
    "CSThreads",		// The number of CS threads processed by the hardware.
//  "CSVALUBusy",		// The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal). 7xxx
//  "CSVALUInsts",		// The average number of vector ALU instructions executed per work-item (affected by flow control). 7xxx
//  "CSVALUUtilization",	// The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence). 7xxx
//  "CSVFetchInsts",		// The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). 7xxx
//  "CSVWriteInsts",		// The average number of vector write instructions to the video memory executed per work-item (affected by flow control). 7xxx
    "CSWavefronts",		// The total number of wavefronts used for the CS.
    "CSWriteInsts",		// The average number of write instructions executed in compute shader per execution. Affected by flow control. The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.
//  "CSWriteSize",		// The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account. 7xxx
//  "CSWriteUnitStalled",	// The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad). 7xxx

    NULL
};

/* ********************************************************************************************
 */
void AppendCounters();
FILE *logfile;
bool MakeProfileRun = false;

void ProfileStart(enum TSPHardware hw, const char *filename) {
  accelerator defa;
  wstring defp = defa.device_path;

  if ((hw == TSPH_AMP_GPU) && defp.find(L"VEN_1002")) {
    /* get the DX11 device */
    accelerator_view defv = defa.default_view;
    IUnknown *devd = Concurrency::direct3d::get_device(defv);
    GPA_Status ret;

    /* start the profiling */
    if ((ret = GPA_Initialize()) != GPA_STATUS_OK) return;
    if ((ret = GPA_OpenContext(devd)) != GPA_STATUS_OK) return;
//  if ((ret = GPA_EnableAllCounters()) != GPA_STATUS_OK) return;

    gpa_uint32 numc, lstp = 1;
    if ((ret = GPA_GetNumCounters(&numc)) == GPA_STATUS_OK) {
#if 0
      fprintf(stderr, "Available counters:\n");

      for (unsigned int cntc = 0; cntc < numc; cntc++) {
	const char *namc;
	if ((ret = GPA_GetCounterName(cntc, &namc)) == GPA_STATUS_OK)
	  fprintf(stderr, " %3d: %s\n", cntc, namc);
      }
#endif

#if 0
      for (unsigned int cntc = 0; !!EnableCounters[cntc]; cntc++) {
	gpa_uint32 nump;
	if ((ret = GPA_EnableCounterStr(EnableCounters[cntc])) == GPA_STATUS_OK)
	if ((ret = GPA_GetPassCount(&nump)) == GPA_STATUS_OK)
	  fprintf(stderr, " %3d: %s +%d passes (%d total)\n", cntc, EnableCounters[cntc], nump - lstp, nump), lstp = nump;
      }
#endif

//    GPA_EnableCounterStr("CSThreads");		// known
//    GPA_EnableCounterStr("CSWavefronts");		// known

      GPA_EnableCounterStr("CSALUBusy");
      GPA_EnableCounterStr("CSTexBusy");

//    GPA_EnableCounterStr("CSALUPacking");
      GPA_EnableCounterStr("CSALUInsts");
      GPA_EnableCounterStr("CSLDSFetchInsts");
      GPA_EnableCounterStr("CSLDSWriteInsts");
      GPA_EnableCounterStr("CSFetchInsts");
      GPA_EnableCounterStr("CSWriteInsts");

      GPA_EnableCounterStr("CSALUStalledByLDS");
      GPA_EnableCounterStr("CSLDSBankConflict");

      GPA_EnableCounterStr("CSFastPath");
//    GPA_EnableCounterStr("CSCompletePath");		// 0 bytes
//    GPA_EnableCounterStr("CSPathUtilization");	// 100%
//    GPA_EnableCounterStr("CSCacheHit");		// 0%

//    GPA_EnableCounterStr("PctTex1D");			// irrelevant
//    GPA_EnableCounterStr("PctTex2D");			// irrelevant

      logfile = fopen(filename, "wb");
      MakeProfileRun = true;
    }
  }
}

void ProfileExit() {
  if (MakeProfileRun) {
//  WriteSession(currentWaitSessionID, filename);
    GPA_DisableAllCounters();
    GPA_CloseContext();
    GPA_Destroy();

    if (logfile)
      fclose(logfile);
  }
}

/* ********************************************************************************************
 */
gpa_uint32 sessionID;

int ProfileBegin() {
  if (MakeProfileRun) {
    gpa_uint32 nump;

    GPA_BeginSession(&sessionID);
    GPA_GetPassCount(&nump);

    return max(1, nump);
  }

  return 1;
}

void ProfileEnd() {
  if (MakeProfileRun) {
    GPA_EndSession();

    if (logfile)
      AppendCounters();
  }
}

/* ********************************************************************************************
 */
void ProfilePassBegin() {
  if (MakeProfileRun) {
    GPA_BeginPass();
  }
}

void ProfilePassEnd() {
  if (MakeProfileRun) {
    GPA_EndPass();
  }
}

/* ********************************************************************************************
 */
void ProfileSampleBegin(int iteration) {
  if (MakeProfileRun) {
    GPA_BeginSample(iteration);
  }
}

void ProfileSampleEnd() {
  if (MakeProfileRun) {
    GPA_EndSample();
  }
}

/* ********************************************************************************************
 */
void AppendCounters() {
  static bool doneHeadings = false;
  gpa_uint32 count;
  GPA_GetEnabledCount(&count);

  if (!doneHeadings) {
    fprintf(logfile, "Permutation, Iteration, ");
    for (gpa_uint32 counter = 0; counter < count; counter++) {
      gpa_uint32 enabledCounterIndex;
      const char *name;

      GPA_GetEnabledIndex(counter, &enabledCounterIndex);
      GPA_GetCounterName(enabledCounterIndex, &name);

      fprintf(logfile, "%s, ", name);
    }

    fprintf(logfile, "\n");
    doneHeadings = true;
  }

  gpa_uint32 sampleCount;
  GPA_GetSampleCount(sessionID, &sampleCount);

  for (gpa_uint32 sample = 0; sample < sampleCount; sample++) {
    fprintf(logfile, "%d, %d, ", sessionID, sample);

    for (gpa_uint32 counter = 0; counter < count; counter++) {
      gpa_uint32 enabledCounterIndex;
      GPA_Type type;
      GPA_Usage_Type usage;
      const char *unit = "";

      GPA_GetEnabledIndex(counter, &enabledCounterIndex);
      GPA_GetCounterDataType(enabledCounterIndex, &type);
      GPA_GetCounterUsageType(enabledCounterIndex, &usage);

      if (usage == GPA_USAGE_TYPE_RATIO) {
	unit = "";
      }
      else if (usage == GPA_USAGE_TYPE_PERCENTAGE) {
	unit = "%";
      }
      else if (usage == GPA_USAGE_TYPE_CYCLES) {
	unit = " cycles";
      }
      else if (usage == GPA_USAGE_TYPE_MILLISECONDS) {
	unit = " ms";
      }
      else if (usage == GPA_USAGE_TYPE_BYTES) {
	unit = " bytes";
      }
      else if (usage == GPA_USAGE_TYPE_ITEMS) {
	unit = " items";
      }
      else if (usage == GPA_USAGE_TYPE_KILOBYTES) {
	unit = " kbytes";
      }

      if (type == GPA_TYPE_UINT32) {
        gpa_uint32 value;
        GPA_GetSampleUInt32(sessionID, sample, enabledCounterIndex, &value);
        if (usage == GPA_USAGE_TYPE_PERCENTAGE) value *= 100;
        fprintf(logfile, "%u%s, ", value, unit);
      }
      else if (type == GPA_TYPE_UINT64) {
        gpa_uint64 value;
        GPA_GetSampleUInt64(sessionID, sample, enabledCounterIndex, &value);
        if (usage == GPA_USAGE_TYPE_PERCENTAGE) value *= 100;
        fprintf(logfile, "%I64u%s, ", value, unit);
      }
      else if (type == GPA_TYPE_FLOAT32) {
        gpa_float32 value;
        GPA_GetSampleFloat32(sessionID, sample, enabledCounterIndex, &value);
        if (usage == GPA_USAGE_TYPE_PERCENTAGE) value *= 100.0f;
        fprintf(logfile, "%f%s, ", value, unit);
      }
      else if (type == GPA_TYPE_FLOAT64) {
        gpa_float64 value;
        GPA_GetSampleFloat64(sessionID, sample, enabledCounterIndex, &value);
        if (usage == GPA_USAGE_TYPE_PERCENTAGE) value *= 100.0;
        fprintf(logfile, "%f%s, ", value, unit);
      }
      else {
        assert(false);
      }
    }

    fprintf(logfile, "\n");
  }
}

#endif
