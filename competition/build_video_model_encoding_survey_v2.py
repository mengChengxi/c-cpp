from __future__ import annotations

import csv
import json
import re
from pathlib import Path
from urllib.request import urlopen


INPUT_CSV = Path("/Users/mengchengxi/Documents/code/C++C/video_model_encoding_survey.csv")
OUTPUT_CSV = Path("/Users/mengchengxi/Desktop/video_model_encoding_survey_complete_english.csv")

LONGVIDEOBENCH_URL = "https://longvideobench.github.io/"
LVBENCH_URL = "https://lvbench.github.io/"
LONGVIDEOBENCH_METHOD_REF = "https://arxiv.org/abs/2407.15754"
LVBENCH_METHOD_REF = (
    "https://openaccess.thecvf.com/content/ICCV2025/papers/"
    "Wang_LVBench_An_Extreme_Long_Video_Understanding_Benchmark_ICCV_2025_paper.pdf"
)
SNAPSHOT_DATE = "2026-04-05"
STANDARDIZED_TOKEN_VALUE = "196"
STANDARDIZED_TOKEN_UNIT = "tokens/frame"


def fetch_text(url: str) -> str:
    with urlopen(url, timeout=30) as response:
        return response.read().decode("utf-8", "ignore")


def fetch_json(url: str) -> dict:
    with urlopen(url, timeout=30) as response:
        return json.load(response)


def norm_name(name: str) -> str:
    name = re.sub(r"\s+\(\d+\)$", "", name.strip())
    name = name.replace("*", "")
    return re.sub(r"[^a-z0-9]+", "", name.lower())


def parse_longvideobench_links() -> dict[str, str]:
    html = fetch_text(LONGVIDEOBENCH_URL)
    rows = {}
    pattern = re.compile(
        r"<th scope=\"col\">(\d+)</th>\s*<th scope=\"row\"><a href='([^']+)'>(.*?)<svg",
        re.S,
    )
    for _, href, text in pattern.findall(html):
        clean = re.sub(r"<.*?>", "", text)
        clean = " ".join(clean.split())
        rows[norm_name(clean)] = href
    return rows


def parse_lvbench_links() -> dict[str, str]:
    html = fetch_text(LVBENCH_URL)
    rows = {}
    pattern = re.compile(
        r"<tr>\s*<td style=\"vertical-align: middle;\">(.*?)</td>\s*"
        r"<td style=\"vertical-align: middle;\">\s*<b class=\"\">\s*"
        r"<a\s+href=\"([^\"]+)\"[^>]*>(.*?)<p",
        re.S,
    )
    for _, href, text in pattern.findall(html):
        clean = re.sub(r"<.*?>", "", text)
        clean = " ".join(clean.split())
        rows[norm_name(clean)] = href
    return rows


def format_num(value: float) -> str:
    return f"{value:.1f}"


def parse_budget(value: str) -> tuple[str | None, float | None]:
    value = value.strip()
    if not value or value == "-":
        return None, None
    if value.startswith("≤"):
        return "le", float(value[1:])
    if value.startswith("<="):
        return "le", float(value[2:])
    if value.startswith(">"):
        return "gt", float(value[1:])
    return "eq", float(value)


def normalize_bound_text(value: str) -> str:
    return value.replace("≤", "<=").strip()


def compute_tpm(benchmark: str, budget_value: str, token_value: str, token_unit: str) -> str:
    if not token_value:
        return "not computable (missing token value for TPM)"
    token = float(token_value)
    budget_mode, budget = parse_budget(budget_value)

    if benchmark == "LongVideoBench":
        if token_unit == "tokens/video":
            low = token / 60.0
            high = token / 15.0
            return f"[{format_num(low)}, {format_num(high)}]"
        if budget is None:
            return "not computable (missing leaderboard frame budget)"
        low = budget * token / 60.0
        high = budget * token / 15.0
        if budget_mode == "eq":
            return f"[{format_num(low)}, {format_num(high)}]"
        prefix = "<=" if budget_mode == "le" else ">"
        return f"{prefix}[{format_num(low)}, {format_num(high)}]"

    if budget is None and token_unit != "tokens/video":
        return "not computable (missing leaderboard frame budget)"

    if token_unit == "tokens/video":
        value = token * 60.0 / 4101.0
    else:
        value = budget * token * 60.0 / 4101.0

    if budget_mode == "eq" or token_unit == "tokens/video":
        return format_num(value)
    if budget_mode == "le":
        return f"<={format_num(value)}"
    if budget_mode == "gt":
        return f">{format_num(value)}"
    return "not computable (unexpected budget format)"


def human_token_status(kind: str) -> str:
    mapping = {
        "fixed_frame": "public fixed tokens/frame",
        "fixed_video": "public fixed tokens/video",
        "image_only": "public fixed tokens/image only; no fixed public video token count; standardized 196 tokens/frame used for TPM",
        "image_range_only": "public token range per image only; no fixed public video token count; standardized 196 tokens/frame used for TPM",
        "image_modes_only": "public image token modes only; no fixed public video token count; standardized 196 tokens/frame used for TPM",
        "query_only": "public query-token count only; no fixed public video token count; standardized 196 tokens/frame used for TPM",
        "undisclosed_standardized": "no public fixed visual token count; standardized 196 tokens/frame used for TPM",
        "undisclosed_not_computable": "no public fixed visual token count and no public leaderboard frame budget; TPM not computable",
    }
    return mapping[kind]


def base_info(
    *,
    access_type: str,
    vision: str,
    llm: str,
    connector: str,
    resolution: str,
    sampling: str,
    temporal: str,
    compression: str,
    public_token_value: str = "",
    public_token_unit: str = "",
    public_token_note: str = "",
    tpm_token_value: str = STANDARDIZED_TOKEN_VALUE,
    tpm_token_unit: str = STANDARDIZED_TOKEN_UNIT,
    token_status_kind: str = "undisclosed_standardized",
    completeness: str = "medium",
    missing: str = "",
    ref_encoding: str = "",
    ref_token: str = "",
    summary: str | None = None,
) -> dict[str, str]:
    if not summary:
        summary = (
            f"Vision={vision}; LLM={llm}; connector/resampler={connector}; "
            f"resolution={resolution}; frame sampling={sampling}; temporal modeling={temporal}; "
            f"compression/tokenization={compression}."
        )
    return {
        "access_type": access_type,
        "vision_encoder_public": vision,
        "language_backbone_public": llm,
        "connector_or_resampler_public": connector,
        "resolution_strategy_public": resolution,
        "frame_sampling_public": sampling,
        "temporal_modeling_public": temporal,
        "compression_strategy_public": compression,
        "public_visual_token_value": public_token_value,
        "public_visual_token_unit": public_token_unit,
        "public_visual_token_note": public_token_note,
        "token_value_used_for_tpm": tpm_token_value,
        "token_unit_used_for_tpm": tpm_token_unit,
        "token_information_status": human_token_status(token_status_kind),
        "encoding_summary": summary,
        "encoding_completeness": completeness,
        "missing_information": missing,
        "reference_encoding": ref_encoding,
        "reference_token": ref_token or ref_encoding,
    }


TRANSFORMERS_LLAVA_ONEVISION = (
    "https://raw.githubusercontent.com/huggingface/transformers/main/"
    "docs/source/en/model_doc/llava_onevision.md"
)
TRANSFORMERS_QWEN2_VL = (
    "https://raw.githubusercontent.com/huggingface/transformers/main/"
    "docs/source/en/model_doc/qwen2_vl.md"
)
OPENREVIEW_LLAVA_VIDEO = "https://openreview.net/pdf?id=8Livf4oZxz"
HF_LLAVA_VIDEO_72B = "https://huggingface.co/lmms-lab/LLaVA-Video-72B-Qwen2/raw/main/README.md"
HF_LLAVA_VIDEO_7B = "https://huggingface.co/lmms-lab/LLaVA-Video-7B-Qwen2/raw/main/README.md"
HF_LLAVA_ONEVISION_72B = "https://huggingface.co/lmms-lab/llava-onevision-qwen2-72b-ov/raw/main/README.md"
HF_INTERNVL2_40B = "https://huggingface.co/OpenGVLab/InternVL2-40B/raw/main/README.md"
HF_INTERNVL25_78B = "https://huggingface.co/OpenGVLab/InternVL2_5-78B/raw/main/README.md"
HF_INTERNVL_CHAT_V15 = "https://huggingface.co/OpenGVLab/InternVL-Chat-V1-5/raw/main/README.md"
RAW_MPLUG_OWL3 = "https://raw.githubusercontent.com/X-PLUG/mPLUG-Owl/main/mPLUG-Owl3/README.md"
HF_MPLUG_OWL3_CFG = "https://huggingface.co/mPLUG/mPLUG-Owl3-7B-241101/raw/main/config.json"
HF_ARIA_CFG = "https://huggingface.co/rhymes-ai/Aria/raw/main/config.json"
RAW_ARIA_README = "https://raw.githubusercontent.com/rhymes-ai/Aria/main/README.md"
RAW_TIMEMARKER = "https://raw.githubusercontent.com/TimeMarker-LLM/TimeMarker/main/README.md"
RAW_MINICPM_V26 = "https://raw.githubusercontent.com/OpenBMB/MiniCPM-V/main/docs/minicpm_v2dot6_en.md"
RAW_KANGAROO = "https://raw.githubusercontent.com/KangarooGroup/Kangaroo/main/README.md"
RAW_PLLAVA = "https://raw.githubusercontent.com/magic-research/PLLaVA/main/README.md"
HF_PHI3_VISION_README = "https://huggingface.co/microsoft/Phi-3-vision-128k-instruct/raw/main/README.md"
HF_PHI3_VISION_CFG = "https://huggingface.co/microsoft/Phi-3-vision-128k-instruct/raw/main/config.json"
HF_IDEFICS2_README = "https://huggingface.co/HuggingFaceM4/idefics2-8b/raw/main/README.md"
HF_IDEFICS2_CFG = "https://huggingface.co/HuggingFaceM4/idefics2-8b/raw/main/config.json"
HF_MANTIS_IDEFICS2 = "https://huggingface.co/TIGER-Lab/Mantis-8B-Idefics2/raw/main/README.md"
HF_MANTIS_BAKLLAVA = "https://huggingface.co/TIGER-Lab/Mantis-bakllava-7b/raw/main/README.md"
HF_BAKLLAVA_CFG = "https://huggingface.co/llava-hf/bakLlava-v1-hf/raw/main/config.json"
HF_BLIP2_CFG = "https://huggingface.co/Salesforce/blip2-flan-t5-xxl/raw/main/config.json"
HF_INSTRUCTBLIP_CFG = "https://huggingface.co/Salesforce/instructblip-flan-t5-xxl/raw/main/config.json"
HF_LLAVA16_M7B_CFG = "https://huggingface.co/llava-hf/llava-v1.6-mistral-7b-hf/raw/main/config.json"
HF_LLAVA16_34B_CFG = "https://huggingface.co/llava-hf/llava-v1.6-34b-hf/raw/main/config.json"
HF_LLAVA15_7B_CFG = "https://huggingface.co/llava-hf/llava-1.5-7b-hf/raw/main/config.json"
HF_LLAVA15_13B_CFG = "https://huggingface.co/llava-hf/llava-1.5-13b-hf/raw/main/config.json"
RAW_SHAREGPT4VIDEO = "https://huggingface.co/Lin-Chen/sharegpt4video-8b/raw/main/README.md"
RAW_VIDEOCHAT2 = "https://raw.githubusercontent.com/OpenGVLab/Ask-Anything/main/video_chat2/README.md"
ARXIV_VIDEOCHAT2 = "https://arxiv.org/pdf/2311.17005"
RAW_VIDEO_LLAVA = "https://raw.githubusercontent.com/PKU-YuanGroup/Video-LLaVA/main/README.md"
ARXIV_DEEP_VIDEO_DISCOVERY = "https://arxiv.org/abs/2505.18079"
RAW_DEEP_VIDEO_DISCOVERY = "https://raw.githubusercontent.com/microsoft/DeepVideoDiscovery/main/README.md"
ARXIV_SEED15 = "https://arxiv.org/abs/2505.07062"
RAW_ADARETAKE = "https://raw.githubusercontent.com/SCZwangxiao/video-FlexReduc/main/README.md"
BIGMODEL_GLM4V = "https://bigmodel.cn/dev/howuse/glm-4v"
GEMINI_REPORT = "https://storage.googleapis.com/deepmind-media/gemini/gemini_v1_5_report.pdf"
RAW_ORYX = "https://raw.githubusercontent.com/Oryx-mllm/Oryx/master/README.md"
COGVLM2_VIDEO = "https://cogvlm2-video.github.io/"
ARXIV_LWM = "https://arxiv.org/abs/2402.08268"
ARXIV_LLAMAVID = "https://arxiv.org/abs/2311.17043"
ARXIV_MOVIECHAT = "https://arxiv.org/abs/2307.16449v4"
RAW_MOVIECHAT = "https://raw.githubusercontent.com/rese1f/MovieChat/main/README.md"
ARXIV_TIMECHAT = "https://arxiv.org/abs/2312.02051"
LLAVA_NEXT_VIDEO_BLOG = "https://llava-vl.github.io/blog/2024-04-30-llava-next-video/"
OPENAI_VISION_GUIDE = "https://developers.openai.com/api/docs/guides/images-vision"
OPENAI_GPT4O_COOKBOOK = "https://developers.openai.com/cookbook/examples/gpt4o/introduction_to_gpt4o"


def openai_closed(model_url: str, public_name: str) -> dict[str, str]:
    model_url = model_url or "https://platform.openai.com/docs/models"
    return base_info(
        access_type="proprietary API",
        vision="public API docs confirm image input and OpenAI Cookbook shows a client-side video-to-frame workflow, but the internal vision encoder is not publicly disclosed",
        llm=f"{public_name} (public model name; internal backbone details not publicly disclosed)",
        connector="not publicly disclosed",
        resolution="public docs describe image detail and resizing behavior, but not the exact leaderboard-run image/video preprocessing recipe",
        sampling="OpenAI Cookbook provides a public client-side frame-extraction example, but the exact leaderboard-run frame-sampling recipe is not publicly disclosed",
        temporal="not publicly disclosed; the public developer workflow commonly converts video into sampled image frames outside the model API",
        compression="public image billing/detail rules exist, but the model's internal visual tokenization is not publicly disclosed",
        token_status_kind="undisclosed_standardized",
        completeness="low",
        missing=(
            "OpenAI publicly documents how developers can send sampled image frames to the API, but does not disclose the internal "
            "vision tower, temporal module, connector, or any fixed visual token count for the benchmark configuration."
        ),
        ref_encoding=f"{model_url} | {OPENAI_VISION_GUIDE} | {OPENAI_GPT4O_COOKBOOK}",
        ref_token=f"{model_url} | {OPENAI_VISION_GUIDE}",
    )


def gemini_closed(model_url: str, public_name: str) -> dict[str, str]:
    model_url = model_url or GEMINI_REPORT
    return base_info(
        access_type="proprietary API",
        vision=f"{public_name} supports multimodal long-context input publicly, but the internal vision tower is not publicly disclosed",
        llm=f"{public_name} (public model name; internal backbone details not publicly disclosed)",
        connector="not publicly disclosed",
        resolution="public materials confirm long-context multimodal support, but not the exact leaderboard-run video preprocessing recipe",
        sampling="not publicly disclosed for the leaderboard run",
        temporal="not publicly disclosed",
        compression="not publicly disclosed",
        token_status_kind="undisclosed_standardized",
        completeness="low",
        missing=(
            "The public materials confirm the product capability, but do not publish the benchmark-run video encoder, temporal "
            "aggregation recipe, connector, or a fixed visual token count."
        ),
        ref_encoding=model_url or GEMINI_REPORT,
        ref_token=model_url or GEMINI_REPORT,
    )


def glm4v_closed(model_url: str, public_name: str) -> dict[str, str]:
    return base_info(
        access_type="proprietary API",
        vision=f"{public_name} is publicly exposed as a multimodal model, but the internal vision tower is not publicly disclosed",
        llm=f"{public_name} (public model name; internal backbone details not publicly disclosed)",
        connector="not publicly disclosed",
        resolution="official API docs confirm visual support; exact benchmark preprocessing is not public",
        sampling="not publicly disclosed for the leaderboard run",
        temporal="not publicly disclosed",
        compression="not publicly disclosed",
        token_status_kind="undisclosed_standardized",
        completeness="low",
        missing=(
            "The public API docs expose the product capability, but do not disclose the model's video-specific visual encoder, "
            "temporal tokenization, connector, or a fixed visual token count for the leaderboard run."
        ),
        ref_encoding=model_url or BIGMODEL_GLM4V,
        ref_token=model_url or BIGMODEL_GLM4V,
    )


def llava_video(model_card_url: str) -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="SigLIP vision encoder",
        llm="Qwen2",
        connector="multimodal projector",
        resolution="video representation built on frame features; released examples use fps-based uniform sampling",
        sampling="released model card examples use fps-based uniform sampling; public checkpoint card states support for at most 64 frames",
        temporal="SlowFast video representation",
        compression="published configuration table reports 169 visual tokens/frame",
        public_token_value="169",
        public_token_unit="tokens/frame",
        public_token_note=(
            "The official paper's visual representation configuration table reports 169 visual tokens per frame."
        ),
        tpm_token_value="169",
        tpm_token_unit="tokens/frame",
        token_status_kind="fixed_frame",
        completeness="high",
        missing=(
            "The leaderboard row uses 128 frames, while the released Hugging Face card says the public checkpoint "
            "supports at most 64 frames. The exact benchmark evaluation configuration is therefore not fully reproduced publicly."
        ),
        ref_encoding=f"{OPENREVIEW_LLAVA_VIDEO} | {model_card_url}",
        ref_token=OPENREVIEW_LLAVA_VIDEO,
    )


def llava_onevision(model_card_url: str) -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="SigLIP / SO400M vision tower",
        llm="Qwen2",
        connector="multimodal projector",
        resolution="any-resolution visual pipeline; video frames are pooled before being passed to the LLM",
        sampling="public docs confirm video support but do not publish the exact leaderboard-run frame sampler",
        temporal="frame-wise video processing with pooled frame features",
        compression="Transformers docs state that video is pooled to 196 tokens per frame",
        public_token_value="196",
        public_token_unit="tokens/frame",
        public_token_note=(
            "The Transformers LLaVA-OneVision docs state that videos are pooled to a total sequence length of 196 tokens each frame."
        ),
        tpm_token_value="196",
        tpm_token_unit="tokens/frame",
        token_status_kind="fixed_frame",
        completeness="high",
        missing=(
            "The public docs expose the per-frame token count, but the exact leaderboard-run frame sampling schedule "
            "and prompt/eval wrapper remain unspecified."
        ),
        ref_encoding=f"{TRANSFORMERS_LLAVA_ONEVISION} | {model_card_url}",
        ref_token=TRANSFORMERS_LLAVA_ONEVISION,
    )


def internvl2_40b() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="InternViT-6B-448px-V1-5",
        llm="Nous-Hermes-2-Yi-34B",
        connector="MLP projector",
        resolution="dynamic image size is supported; public video evaluation examples resize frames to 448x448",
        sampling="public video evaluation notes mention 16 sampled frames",
        temporal="frame-wise video input packing; no dedicated fixed public temporal compressor located in this pass",
        compression="MLP projection into the LLM; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The architecture is public, but the public materials do not disclose a fixed visual token count for video, "
            "nor the exact leaderboard-run sampling/compression recipe."
        ),
        ref_encoding=HF_INTERNVL2_40B,
        ref_token=HF_INTERNVL2_40B,
    )


def internvl25_78b() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="InternViT-6B-448px-V2_5",
        llm="Qwen2.5-72B-Instruct",
        connector="MLP projector",
        resolution="dynamic resolution with pixel unshuffle; public docs say pixel unshuffle reduces visual tokens to one quarter",
        sampling="public docs describe 448x448 video frames; no fixed public leaderboard-run sampler beyond the benchmark frame budget",
        temporal="frame-wise video packing; no dedicated fixed public temporal compressor located in this pass",
        compression="pixel unshuffle before projector; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public docs disclose the backbone and pixel-unshuffle compression idea, but not a fixed visual token count "
            "or the exact leaderboard-run sampling/compression settings."
        ),
        ref_encoding=HF_INTERNVL25_78B,
        ref_token=HF_INTERNVL25_78B,
    )


def internvl_chat_v15() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="InternViT-6B-448px-V1-5",
        llm="InternLM2-Chat-20B",
        connector="MLP projector",
        resolution="dynamic high resolution up to 40 tiles of 448x448",
        sampling="no fixed public video sampling schedule for the leaderboard run",
        temporal="frame-wise video input packing; no dedicated public temporal compressor located in this pass",
        compression="dynamic tiling plus MLP projection; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The backbone stack is public, but the benchmark-run video token count and exact temporal compression "
            "recipe are not explicitly disclosed."
        ),
        ref_encoding=HF_INTERNVL_CHAT_V15,
        ref_token=HF_INTERNVL_CHAT_V15,
    )


def mplug_owl3(model_url: str, name_specific: str) -> dict[str, str]:
    llm = "Qwen2-family language backbone" if "7B" in name_specific else "Qwen2-family language backbone (exact size not restated on the LVBench row)"
    return base_info(
        access_type="open weights",
        vision="SigLIP vision model (HF config image_size 378, patch_size 14)",
        llm=llm,
        connector="not clearly restated in the public 7B config retrieved in this pass",
        resolution="long image-sequence / long video understanding; public config uses a 378px vision tower",
        sampling="public example code samples video around 1 fps and uniformly downsamples to 16 frames",
        temporal="long image-sequence/video understanding is public, but the exact temporal aggregation block is not fully described in the retrieved sources",
        compression="no fixed public visual token count located",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public sources expose the vision-tower family and example frame sampler, but not a fixed visual token count "
            "or a fully explicit benchmark-run connector/compression recipe."
        ),
        ref_encoding=f"{RAW_MPLUG_OWL3} | {HF_MPLUG_OWL3_CFG}",
        ref_token=f"{RAW_MPLUG_OWL3} | {HF_MPLUG_OWL3_CFG}",
    )


def timemarker() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="not clearly disclosed in the retrieved README",
        llm="Llama3-8B",
        connector="temporal separator token interface",
        resolution="adaptive token resizing is public; exact leaderboard-run image resolution policy is not fully disclosed",
        sampling="dynamic frame sampling",
        temporal="Temporal Separator Tokens and AnyLength long-video inference",
        compression="adaptive token resizing and token merging",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public README describes the temporal/token compression strategy, but does not clearly identify the vision tower "
            "or publish a fixed visual token count for the leaderboard run."
        ),
        ref_encoding=RAW_TIMEMARKER,
        ref_token=RAW_TIMEMARKER,
    )


def minicpm_v26() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="SigLip-400M",
        llm="Qwen2-7B",
        connector="not fully detailed in the retrieved docs",
        resolution="supports high-resolution inputs up to 1.8M pixels",
        sampling="public video example uses roughly 1 fps and uniform downsampling up to 64 frames",
        temporal="video support is public, but the exact temporal aggregation block is not explicitly broken out in the retrieved docs",
        compression="public docs state 640 tokens for a 1.8M-pixel image; no fixed video tokens/frame count is disclosed",
        public_token_value="640",
        public_token_unit="tokens/image",
        public_token_note="The official MiniCPM-V 2.6 docs say the model produces only 640 tokens for a 1.8M-pixel image.",
        token_status_kind="image_only",
        completeness="medium",
        missing=(
            "Public materials disclose an image-side token count at a large pixel budget, but not a fixed video tokens/frame count "
            "or the exact leaderboard-run temporal compression settings."
        ),
        ref_encoding=RAW_MINICPM_V26,
        ref_token=RAW_MINICPM_V26,
    )


def qwen2_vl(model_size: str, extra_missing: str = "") -> dict[str, str]:
    missing = (
        "Public materials disclose the dynamic-resolution policy and an image-token range example, but not a fixed "
        "video tokens/frame count for the leaderboard run."
    )
    if extra_missing:
        missing = f"{missing} {extra_missing}"
    return base_info(
        access_type="open weights",
        vision=f"Qwen2-VL vision stack ({model_size})",
        llm=f"Qwen2-VL language backbone ({model_size})",
        connector="native multimodal Qwen2-VL stack",
        resolution="Naive Dynamic Resolution",
        sampling="no fixed public leaderboard-run frame sampler located in this pass",
        temporal="M-RoPE for spatial and temporal position encoding",
        compression="dynamic token budget tied to pixel count; no fixed public video token count",
        public_token_value="256-1024",
        public_token_unit="tokens/image",
        public_token_note=(
            "The Transformers docs give an example in which each image is encoded into 256-1024 tokens based on min_pixels/max_pixels; "
            "this is not a fixed video tokens/frame count."
        ),
        token_status_kind="image_range_only",
        completeness="medium",
        missing=missing,
        ref_encoding=TRANSFORMERS_QWEN2_VL,
        ref_token=TRANSFORMERS_QWEN2_VL,
    )


def kangaroo() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="not clearly disclosed in the retrieved README",
        llm="Llama3-8B",
        connector="not clearly disclosed in the retrieved README",
        resolution="curriculum training with increasing resolution and frame count",
        sampling="public README states support for up to 160 frames",
        temporal="long-context video input handling for very long sequences",
        compression="README states up to 22k total sequence length, but does not isolate a fixed visual token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public README discloses the long-context budget, but not the exact vision tower, fixed visual token count, "
            "or the leaderboard-run temporal compression recipe."
        ),
        ref_encoding=RAW_KANGAROO,
        ref_token=RAW_KANGAROO,
    )


def pllava(size_label: str) -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="inherits the underlying LLaVA vision tower from the selected base checkpoint",
        llm=f"inherits the underlying LLaVA language backbone for the {size_label} checkpoint",
        connector="parameter-free temporal pooling over LLaVA features",
        resolution="inherits the base LLaVA image-resolution policy",
        sampling="no fixed public leaderboard-run frame sampler located in this pass",
        temporal="temporal pooling smooths features along the time dimension",
        compression="parameter-free temporal pooling; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The temporal pooling strategy is public, but the exact base checkpoint details for the leaderboard submission "
            "and the fixed video token count are not explicitly disclosed on the leaderboard row."
        ),
        ref_encoding=RAW_PLLAVA,
        ref_token=RAW_PLLAVA,
    )


def llava_next_video_34b() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="LLaVA-NeXT vision stack at 336px (public config family)",
        llm="Nous-Hermes-2-Yi-34B / Yi-34B family",
        connector="multimodal projector",
        resolution="LLaVA-NeXT high-resolution image pipeline extended to video",
        sampling="public blog confirms video support, but not the exact leaderboard-run sampler",
        temporal="video extension over frame features; no fixed public temporal compression token count",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public blog confirms the video extension, but does not publish a fixed visual token count or the exact "
            "leaderboard-run sampling recipe."
        ),
        ref_encoding=f"{LLAVA_NEXT_VIDEO_BLOG} | {HF_LLAVA16_34B_CFG}",
        ref_token=f"{LLAVA_NEXT_VIDEO_BLOG} | {HF_LLAVA16_34B_CFG}",
    )


def llava_next_video_m7b() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="LLaVA-NeXT vision stack at 336px (public config family)",
        llm="Mistral-7B-Instruct-v0.2 family",
        connector="multimodal projector",
        resolution="LLaVA-NeXT high-resolution image pipeline extended to video",
        sampling="public blog confirms video support, but not the exact leaderboard-run sampler",
        temporal="video extension over frame features; no fixed public temporal compression token count",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public blog confirms the video extension, but does not publish a fixed visual token count or the exact "
            "leaderboard-run sampling recipe."
        ),
        ref_encoding=f"{LLAVA_NEXT_VIDEO_BLOG} | {HF_LLAVA16_M7B_CFG}",
        ref_token=f"{LLAVA_NEXT_VIDEO_BLOG} | {HF_LLAVA16_M7B_CFG}",
    )


def llava_next_mistral_7b() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="CLIP vision model at 336px, patch size 14",
        llm="Mistral-7B-Instruct-v0.2",
        connector="multimodal projector",
        resolution="336px image pipeline; benchmark video input is handled as sampled frames",
        sampling="leaderboard row exposes the frame budget only; no public fixed frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module; sampled frames are packed through the image pipeline",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The base image-side architecture is public, but the exact video-side tokenization and benchmark-run sampling "
            "recipe are not explicitly disclosed."
        ),
        ref_encoding=HF_LLAVA16_M7B_CFG,
        ref_token=HF_LLAVA16_M7B_CFG,
    )


def llava15(size_label: str, llm: str, cfg_url: str) -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="CLIP vision model at 336px, patch size 14",
        llm=llm,
        connector="multimodal projector",
        resolution="336px image pipeline; leaderboard video input is handled as sampled frames",
        sampling="leaderboard row exposes the frame budget only; no public fixed video sampling recipe found",
        temporal="no dedicated public video-native temporal module; sampled frames are packed through the image model path",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            f"The public config exposes the {size_label} image-side stack, but not a fixed video token count "
            "or a leaderboard-specific temporal compression recipe."
        ),
        ref_encoding=cfg_url,
        ref_token=cfg_url,
    )


def phi3_vision() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="openai/clip-vit-large-patch14-336 image encoder",
        llm="Phi-3 Mini",
        connector="connector plus projector",
        resolution="image-side config exposes an image encoder path; no separate public leaderboard-run video-resolution recipe",
        sampling="leaderboard row exposes frame budget only; no fixed public frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module located in this pass",
        compression="HF config exposes num_img_tokens=144 on the image side; no fixed video tokens/frame count is public",
        public_token_value="144",
        public_token_unit="tokens/image",
        public_token_note="The Hugging Face config exposes img_processor.num_img_tokens=144; this is an image-side setting, not a fixed video tokens/frame count.",
        token_status_kind="image_only",
        completeness="medium",
        missing=(
            "The public config exposes an image-side token count, but not a fixed video tokens/frame count or a dedicated "
            "benchmark-run temporal aggregation recipe."
        ),
        ref_encoding=f"{HF_PHI3_VISION_README} | {HF_PHI3_VISION_CFG}",
        ref_token=HF_PHI3_VISION_CFG,
    )


def idefics2() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="SigLIP vision encoder",
        llm="Mistral-7B-v0.1",
        connector="Perceiver pooling plus MLP projection",
        resolution="native resolution with optional image splitting",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module located in this pass",
        compression="64 tokens/image without image splitting, 320 tokens/image with image splitting",
        public_token_value="64/320",
        public_token_unit="tokens/image",
        public_token_note=(
            "The official Idefics2 model card documents 64 tokens per image without splitting and 320 tokens per image with splitting."
        ),
        token_status_kind="image_modes_only",
        completeness="medium",
        missing=(
            "The public sources disclose image-side token modes, but not a fixed video tokens/frame count for the leaderboard run."
        ),
        ref_encoding=f"{HF_IDEFICS2_README} | {HF_IDEFICS2_CFG}",
        ref_token=HF_IDEFICS2_README,
    )


def mantis_idefics2() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="inherits the Idefics2 SigLIP vision encoder",
        llm="inherits the Idefics2 Mistral-7B backbone",
        connector="inherits the Idefics2 Perceiver pooling plus MLP projection",
        resolution="interleaved text-image inputs on top of Idefics2",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="interleaved frame reasoning on top of an image-native base; no dedicated public video-native temporal module located in this pass",
        compression="inherits Idefics2 image token modes (64 or 320 tokens/image), but no fixed public video token count",
        public_token_value="64/320",
        public_token_unit="tokens/image",
        public_token_note="Mantis-Idefics2 is built on top of Idefics2 and therefore inherits its documented 64/320 tokens-per-image modes, not a fixed video tokens/frame count.",
        token_status_kind="image_modes_only",
        completeness="medium",
        missing=(
            "The base Idefics2 image-side tokenization is public, but the benchmark-run video token count and exact temporal recipe "
            "for this Mantis variant are not publicly fixed."
        ),
        ref_encoding=f"{HF_MANTIS_IDEFICS2} | {HF_IDEFICS2_README}",
        ref_token=HF_IDEFICS2_README,
    )


def instructblip() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="InstructBLIP vision model",
        llm="Flan-T5-XXL",
        connector="Q-Former",
        resolution="image-native pipeline; leaderboard video input is handled through sampled frames",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module located in this pass",
        compression="Q-Former with 32 query tokens per image; no fixed public video token count",
        public_token_value="32",
        public_token_unit="tokens/image",
        public_token_note="The Hugging Face config exposes num_query_tokens=32 for InstructBLIP.",
        token_status_kind="query_only",
        completeness="medium",
        missing=(
            "The public config exposes the image-side Q-Former token count, but not a fixed video tokens/frame count "
            "or a benchmark-run temporal aggregation recipe."
        ),
        ref_encoding=HF_INSTRUCTBLIP_CFG,
        ref_token=HF_INSTRUCTBLIP_CFG,
    )


def mantis_bakllava() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="inherits BakLLaVA's CLIP vision model at 336px, patch size 14",
        llm="inherits BakLLaVA's Mistral-7B-v0.1 backbone",
        connector="inherits BakLLaVA/LLaVA projector",
        resolution="interleaved text-image inputs on top of BakLLaVA",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="interleaved frame reasoning on top of an image-native base; no dedicated public video-native temporal module located in this pass",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The base BakLLaVA image-side architecture is public, but the benchmark-run video token count and exact temporal recipe "
            "for this Mantis variant are not publicly fixed."
        ),
        ref_encoding=f"{HF_MANTIS_BAKLLAVA} | {HF_BAKLLAVA_CFG}",
        ref_token=f"{HF_MANTIS_BAKLLAVA} | {HF_BAKLLAVA_CFG}",
    )


def blip2() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="BLIP-2 vision model",
        llm="Flan-T5-XXL",
        connector="Q-Former",
        resolution="image-native pipeline; leaderboard video input is handled through sampled frames",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module located in this pass",
        compression="Q-Former with 32 query tokens per image; no fixed public video token count",
        public_token_value="32",
        public_token_unit="tokens/image",
        public_token_note="The Hugging Face config exposes num_query_tokens=32 for BLIP-2.",
        token_status_kind="query_only",
        completeness="medium",
        missing=(
            "The public config exposes the image-side Q-Former token count, but not a fixed video tokens/frame count "
            "or a benchmark-run temporal aggregation recipe."
        ),
        ref_encoding=HF_BLIP2_CFG,
        ref_token=HF_BLIP2_CFG,
    )


def sharegpt4video() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="not clearly disclosed in the retrieved model card",
        llm="8B video-language model (exact base not clearly restated in the retrieved model card)",
        connector="not clearly disclosed in the retrieved model card",
        resolution="video chatbot fine-tuned for video instruction following; exact benchmark-run preprocessing is not public",
        sampling="no fixed public leaderboard-run frame sampler located in this pass",
        temporal="video-language fine-tuning is public, but the exact temporal aggregation block is not clearly documented in the retrieved model card",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="low",
        missing=(
            "The retrieved public model card does not clearly restate the exact base vision tower, connector, or fixed visual token count "
            "for the leaderboard submission."
        ),
        ref_encoding=RAW_SHAREGPT4VIDEO,
        ref_token=RAW_SHAREGPT4VIDEO,
    )


def videochat2(llm: str) -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="UMT-L visual encoder",
        llm=llm,
        connector="Q-Former",
        resolution="video-native encoder with staged alignment/training",
        sampling="no fixed public leaderboard-run frame-sampling recipe found beyond the benchmark frame budget",
        temporal="video-native Q-Former over UMT-L features",
        compression="paper's later stages use a total of 96 Q-Former queries per video",
        public_token_value="96",
        public_token_unit="tokens/video",
        public_token_note=(
            "The public VideoChat2 paper describes 32 Q-Former queries in stage 1 and 96 total queries in later stages; "
            "this is the closest public token figure, though not a separate leaderboard-run statement."
        ),
        tpm_token_value="96",
        tpm_token_unit="tokens/video",
        token_status_kind="fixed_video",
        completeness="high",
        missing=(
            "The query-token count is public from the paper's staged design, but the exact benchmark-run prompt/eval wrapper "
            "is not fully specified."
        ),
        ref_encoding=f"{RAW_VIDEOCHAT2} | {ARXIV_VIDEOCHAT2}",
        ref_token=ARXIV_VIDEOCHAT2,
    )


def mplug_owl2() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="ViT-L (0.3B)",
        llm="LLaMA (7B)",
        connector="visual abstractor",
        resolution="image-native pipeline; leaderboard video input is handled through sampled frames",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="no dedicated public video-native temporal module located in this pass",
        compression="visual abstractor is public, but no fixed public video token count is disclosed",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The base image-side stack and visual abstractor are public, but the benchmark-run video token count and temporal recipe "
            "are not explicitly disclosed."
        ),
        ref_encoding="https://raw.githubusercontent.com/X-PLUG/mPLUG-Owl/main/mPLUG-Owl2/README.md",
        ref_token="https://raw.githubusercontent.com/X-PLUG/mPLUG-Owl/main/mPLUG-Owl2/README.md",
    )


def videollava() -> dict[str, str]:
    return base_info(
        access_type="open weights",
        vision="LanguageBind / united visual representation",
        llm="LLaMA-family language model",
        connector="alignment before projection",
        resolution="unified image/video representation before projection",
        sampling="public examples often sample 8 frames uniformly",
        temporal="video understanding through a unified representation rather than a separately described temporal compressor",
        compression="no fixed public video token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public repo explains the unified visual-representation idea, but does not publish a fixed visual token count "
            "for the leaderboard run."
        ),
        ref_encoding=RAW_VIDEO_LLAVA,
        ref_token=RAW_VIDEO_LLAVA,
    )


def deep_video_discovery() -> dict[str, str]:
    return base_info(
        access_type="research system",
        vision="agentic search over segmented video clips; no single fixed public vision tower is the whole story",
        llm="official repo says the benchmark result uses OpenAI o3",
        connector="search/controller over candidate video segments",
        resolution="segment-and-search system rather than a single monolithic visual encoder recipe",
        sampling="leaderboard row does not disclose a concrete frame budget",
        temporal="explicit clip retrieval and iterative search across long videos",
        compression="no fixed public visual token count located; system is not described as a single fixed tokens/frame pipeline",
        token_status_kind="undisclosed_not_computable",
        completeness="medium",
        missing=(
            "This is an agentic long-video system rather than a single monolithic video encoder. The leaderboard row does not expose "
            "a concrete frame budget, so TPM is not computable from public materials."
        ),
        ref_encoding=f"{ARXIV_DEEP_VIDEO_DISCOVERY} | {RAW_DEEP_VIDEO_DISCOVERY}",
        ref_token=f"{ARXIV_DEEP_VIDEO_DISCOVERY} | {RAW_DEEP_VIDEO_DISCOVERY}",
    )


def seed15_vl() -> dict[str, str]:
    return base_info(
        access_type="paper / unclear release",
        vision="532M-parameter vision encoder",
        llm="MoE LLM with 20B active parameters",
        connector="not clearly disclosed in the retrieved technical report abstract",
        resolution="not clearly disclosed in the retrieved technical report abstract",
        sampling="leaderboard row does not disclose a concrete frame budget",
        temporal="not clearly disclosed in the retrieved technical report abstract",
        compression="no fixed public visual token count located in this pass",
        token_status_kind="undisclosed_not_computable",
        completeness="low",
        missing=(
            "The retrieved public material exposes headline backbone sizes, but not the benchmark-run frame budget, connector, "
            "or any fixed video token count. TPM is therefore not computable from public materials."
        ),
        ref_encoding=ARXIV_SEED15,
        ref_token=ARXIV_SEED15,
    )


def adaretake() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="exact leaderboard backbone not fully disclosed in the retrieved README",
        llm="exact leaderboard backbone not fully disclosed in the retrieved README",
        connector="adaptive redundancy-reduction stack",
        resolution="adaptive redundancy reduction across long videos",
        sampling="public repo focuses on extending context capacity from 256 to 2048 frames through reduction",
        temporal="layer-wise and timestamp-wise compression",
        compression="adaptive redundancy reduction; no fixed public visual token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public repo clearly documents the compression idea, but not the exact benchmark-run base model stack "
            "or a fixed video tokens/frame count."
        ),
        ref_encoding=RAW_ADARETAKE,
        ref_token=RAW_ADARETAKE,
    )


def oryx34b() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="Oryx-ViT",
        llm="Yi-1.5-34B",
        connector="dynamic compressor",
        resolution="native-resolution perception",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="long-video handling with dynamic compression; exact temporal block is not broken out separately in the retrieved README",
        compression="dynamic compressor; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The public repo exposes the vision tower family and dynamic-compressor idea, but not a fixed visual token count "
            "for the leaderboard run."
        ),
        ref_encoding=RAW_ORYX,
        ref_token=RAW_ORYX,
    )


def cogvlm2_video() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="CogVLM2-Video timestamp-aware frame encoder",
        llm="CogVLM2-Video language backbone",
        connector="native multimodal stack",
        resolution="video-native timestamp-aware frame inputs",
        sampling="leaderboard row exposes frame budget only; no fixed public video frame-sampling recipe found",
        temporal="explicit timestamp-aware temporal modeling",
        compression="project page emphasizes precise timestamp modeling over temporal pooling/Q-Former compression; no fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The project page describes the timestamp-aware design, but does not publish a fixed visual token count "
            "for the leaderboard run."
        ),
        ref_encoding=COGVLM2_VIDEO,
        ref_token=COGVLM2_VIDEO,
    )


def lwm() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="long-context video-language stack; exact vision tower for the leaderboard run not fully restated in the abstract",
        llm="LWM long-context language backbone",
        connector="long-context multimodal integration",
        resolution="supports very long multimodal contexts up to 1M tokens",
        sampling="leaderboard row exposes only a lower bound on frames (>3600)",
        temporal="long-context temporal reasoning through extremely long sequence modeling",
        compression="no fixed public visual token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="low",
        missing=(
            "The public abstract highlights the 1M-token context capability, but does not publish the fixed visual tokenization "
            "recipe or the exact leaderboard-run video encoder settings."
        ),
        ref_encoding=ARXIV_LWM,
        ref_token=ARXIV_LWM,
    )


def llama_vid() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="LLaVA-style video encoder with context/content tokenization",
        llm="LLaMA-VID language backbone",
        connector="context/content token interface",
        resolution="long-video handling via aggressive frame compression",
        sampling="leaderboard row exposes only a lower bound on frames (>10800)",
        temporal="long-video reasoning over compressed per-frame tokens",
        compression="official paper states each frame is represented with 2 tokens",
        public_token_value="2",
        public_token_unit="tokens/frame",
        public_token_note="The official LLaMA-VID paper states that each frame is represented with two tokens: one context token and one content token.",
        tpm_token_value="2",
        tpm_token_unit="tokens/frame",
        token_status_kind="fixed_frame",
        completeness="high",
        missing=(
            "The aggressive per-frame token count is public, but the exact leaderboard-run prompt/eval wrapper is not fully specified."
        ),
        ref_encoding=ARXIV_LLAMAVID,
        ref_token=ARXIV_LLAMAVID,
    )


def moviechat() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="Video-LLaMA-style long-video stack",
        llm="MovieChat language backbone",
        connector="sparse-memory mechanism",
        resolution="supports very long videos with sparse memory",
        sampling="leaderboard row exposes only a lower bound on frames (>10000)",
        temporal="sparse memory for long-range temporal reasoning",
        compression="sparse-memory design; no fixed public visual token count located in this pass",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The sparse-memory long-video idea is public, but the public sources do not publish a fixed visual token count "
            "for the leaderboard run."
        ),
        ref_encoding=f"{ARXIV_MOVIECHAT} | {RAW_MOVIECHAT}",
        ref_token=f"{ARXIV_MOVIECHAT} | {RAW_MOVIECHAT}",
    )


def timechat() -> dict[str, str]:
    return base_info(
        access_type="open repo / paper",
        vision="timestamp-aware frame encoder",
        llm="TimeChat language backbone",
        connector="sliding video Q-Former",
        resolution="timestamp-aware video pipeline; exact public leaderboard-run resolution recipe is not fully disclosed",
        sampling="leaderboard row exposes only a lower bound on frames (>96)",
        temporal="timestamp-aware modeling with sliding windows",
        compression="varying-length video token sequence; no single fixed public video token count",
        token_status_kind="undisclosed_standardized",
        completeness="medium",
        missing=(
            "The timestamp-aware temporal design is public, but there is no single fixed public visual token count "
            "for the leaderboard run."
        ),
        ref_encoding=ARXIV_TIMECHAT,
        ref_token=ARXIV_TIMECHAT,
    )


def fill_model_info(model_name: str, official_model_url: str) -> dict[str, str]:
    if model_name in {"GPT-4o (0513)", "GPT-4o-mini", "GPT-4o-2024-11-20", "GPT-4o (2024-05-13)", "GPT-4o"}:
        return openai_closed(official_model_url, model_name)
    if model_name == "GPT-4-Turbo (0409)":
        return openai_closed(official_model_url, model_name)
    if model_name in {"Gemini-1.5-Pro (0514)", "Gemini 1.5 Pro", "Gemini-1.5-Flash (0514)"}:
        return gemini_closed(official_model_url or GEMINI_REPORT, model_name)
    if model_name in {"GLM-4V-Plus-0111", "GLM-4V-Plus"}:
        return glm4v_closed(official_model_url or BIGMODEL_GLM4V, model_name)
    if model_name == "Aria":
        return base_info(
            access_type="open weights",
            vision="AriaVisionModel / Idefics3-style vision tower (config model_type idefics3_vision, image_size 980)",
            llm="Aria multimodal native MoE text backbone",
            connector="projector patch-to-query mapping",
            resolution="native-resolution visual path with patch-budget-dependent query compression",
            sampling="video datasets are supported, but no fixed public leaderboard-run frame sampler was located in this pass",
            temporal="video support is public, but a dedicated temporal module is not clearly separated in the retrieved sources",
            compression="config exposes projector_patch_to_query_dict mapping 1225 patches to 128 queries and 4900 patches to 256 queries",
            public_token_value="128/256",
            public_token_unit="tokens/image",
            public_token_note="Aria's public config exposes projector_patch_to_query_dict={1225:128, 4900:256}; this is an image-side query budget, not a fixed video tokens/frame count.",
            token_status_kind="image_only",
            completeness="medium",
            missing=(
                "The public config exposes image-side query compression, but not a fixed video tokens/frame count or the exact "
                "leaderboard-run temporal sampling recipe."
            ),
            ref_encoding=f"{HF_ARIA_CFG} | {RAW_ARIA_README}",
            ref_token=HF_ARIA_CFG,
        )
    if model_name == "LLaVA-Video-72B-Qwen2":
        return llava_video(HF_LLAVA_VIDEO_72B)
    if model_name == "LLaVA-Video-7B-Qwen2":
        return llava_video(HF_LLAVA_VIDEO_7B)
    if model_name == "LLaVA-OneVision-Qwen2-72B-OV":
        return llava_onevision(HF_LLAVA_ONEVISION_72B)
    if model_name == "InternVL2-40B":
        return internvl2_40b()
    if model_name == "InternVL2.5-78B":
        return internvl25_78b()
    if model_name == "InternVL-Chat-V1-5-26B":
        return internvl_chat_v15()
    if model_name in {"mPLUG-Owl3-7B", "mPLUG-Owl3"}:
        return mplug_owl3(official_model_url, model_name)
    if model_name == "TimeMarker":
        return timemarker()
    if model_name == "MiniCPM-V-2.6":
        return minicpm_v26()
    if model_name == "Qwen2-VL-7B":
        return qwen2_vl(
            "7B",
            "As of 2026-04-05, the LongVideoBench leaderboard link on the page points to MiniCPM-V-2_6 rather than Qwen2-VL-7B, so the model URL was manually corrected in this CSV.",
        )
    if model_name == "Qwen2-VL-72B":
        return qwen2_vl("72B")
    if model_name == "Kangaroo":
        return kangaroo()
    if model_name in {"PLLaVA-34B", "PLLaVA 34B"}:
        return pllava("34B")
    if model_name == "PLLaVA-13B":
        return pllava("13B")
    if model_name == "PLLaVA-7B":
        return pllava("7B")
    if model_name == "LLaVA-Next-Video-34B":
        return llava_next_video_34b()
    if model_name == "LLaVA-NeXT-Video-DPO (34B)":
        return llava_next_video_34b()
    if model_name == "LLaVA-Next-Video-M7B":
        return llava_next_video_m7b()
    if model_name == "LLaVA-Next-Mistral-7B":
        return llava_next_mistral_7b()
    if model_name == "Phi-3-Vision-Instruct":
        return phi3_vision()
    if model_name == "Idefics2":
        return idefics2()
    if model_name == "Mantis-Idefics2":
        return mantis_idefics2()
    if model_name == "InstructBLIP-T5-XXL":
        return instructblip()
    if model_name == "Mantis-BakLLaVA":
        return mantis_bakllava()
    if model_name == "BLIP-2-T5-XXL":
        return blip2()
    if model_name == "LLaVA-1.5-13B":
        return llava15("13B", "Llama-2-13B", HF_LLAVA15_13B_CFG)
    if model_name == "LLaVA-1.5-7B":
        return llava15("7B", "Vicuna-7B-v1.5", HF_LLAVA15_7B_CFG)
    if model_name == "ShareGPT4Video":
        return sharegpt4video()
    if model_name == "VideoChat2 (Mistral-7B)":
        return videochat2("Mistral-7B")
    if model_name == "VideoChat2 (Vicuna-7B)":
        return videochat2("Vicuna-7B")
    if model_name == "mPLUG-Owl2":
        return mplug_owl2()
    if model_name == "VideoLLaVA":
        return videollava()
    if model_name == "Deep Video Discovery":
        return deep_video_discovery()
    if model_name == "Seed1.5-VL-Thinking":
        return seed15_vl()
    if model_name == "AdaReTaKe":
        return adaretake()
    if model_name == "Oryx-34B":
        return oryx34b()
    if model_name == "CogVLM2-Video":
        return cogvlm2_video()
    if model_name == "LWM":
        return lwm()
    if model_name == "LLaMA-VID":
        return llama_vid()
    if model_name == "MovieChat":
        return moviechat()
    if model_name == "TimeChat":
        return timechat()
    raise KeyError(f"No model info template for: {model_name}")


OUTPUT_FIELDS = [
    "leaderboard_snapshot_date",
    "benchmark",
    "leaderboard_rank",
    "model_name",
    "access_type",
    "leaderboard_budget_field",
    "leaderboard_budget_value",
    "vision_encoder_public",
    "language_backbone_public",
    "connector_or_resampler_public",
    "resolution_strategy_public",
    "frame_sampling_public",
    "temporal_modeling_public",
    "compression_strategy_public",
    "encoding_summary",
    "encoding_completeness",
    "missing_information",
    "public_visual_token_value",
    "public_visual_token_unit",
    "public_visual_token_note",
    "token_information_status",
    "token_value_used_for_tpm",
    "token_unit_used_for_tpm",
    "tpm_estimate",
    "tpm_method_note",
    "official_leaderboard_url",
    "official_model_url",
    "reference_tpm_method",
    "reference_encoding",
    "reference_token",
]


def build_rows() -> list[dict[str, str]]:
    with INPUT_CSV.open("r", encoding="utf-8-sig", newline="") as handle:
        input_rows = list(csv.DictReader(handle))

    long_links = parse_longvideobench_links()
    lv_links = parse_lvbench_links()
    manual_link_overrides = {
        "GPT-4o (0513)": "https://platform.openai.com/docs/models/gpt-4o",
        "GPT-4-Turbo (0409)": "https://platform.openai.com/docs/models/gpt-4-turbo-and-gpt-4",
        "Gemini-1.5-Pro (0514)": "https://console.cloud.google.com/vertex-ai/publishers/google/model-garden/gemini-1.5-pro-001",
        "Gemini-1.5-Flash (0514)": "https://console.cloud.google.com/vertex-ai/publishers/google/model-garden/gemini-1.5-flash-001",
        "Qwen2-VL-7B": "https://huggingface.co/Qwen/Qwen2-VL-7B-Instruct",
    }

    output_rows: list[dict[str, str]] = []
    for row in input_rows:
        benchmark = row["benchmark"]
        model_name = row["model_name"]
        leaderboard_url = LONGVIDEOBENCH_URL if benchmark == "LongVideoBench" else LVBENCH_URL
        tpm_ref = LONGVIDEOBENCH_METHOD_REF if benchmark == "LongVideoBench" else LVBENCH_METHOD_REF
        tpm_method_note = (
            "TPM is computed from the benchmark's 15-60 minute long-video bucket. "
            "For tokens/frame rows: TPM range = frames * token_value / [60, 15]. "
            "For tokens/video rows: TPM range = token_value / [60, 15]."
            if benchmark == "LongVideoBench"
            else "TPM is computed with the benchmark paper's reported 4101-second average video duration. "
            "For tokens/frame rows: TPM = frames * token_value * 60 / 4101. "
            "For tokens/video rows: TPM = token_value * 60 / 4101."
        )

        official_model_url = manual_link_overrides.get(model_name)
        if not official_model_url:
            lookup = long_links if benchmark == "LongVideoBench" else lv_links
            official_model_url = lookup.get(norm_name(model_name), "")

        model_info = fill_model_info(model_name, official_model_url)
        tpm_estimate = compute_tpm(
            benchmark,
            row["leaderboard_budget_value"],
            model_info["token_value_used_for_tpm"],
            model_info["token_unit_used_for_tpm"],
        )

        output_rows.append(
            {
                "leaderboard_snapshot_date": SNAPSHOT_DATE,
                "benchmark": benchmark,
                "leaderboard_rank": row["leaderboard_rank"],
                "model_name": model_name,
                "access_type": model_info["access_type"],
                "leaderboard_budget_field": row["leaderboard_budget_field"],
                "leaderboard_budget_value": normalize_bound_text(row["leaderboard_budget_value"]),
                "official_leaderboard_url": leaderboard_url,
                "official_model_url": official_model_url,
                "reference_tpm_method": tpm_ref,
                "tpm_method_note": tpm_method_note,
                "vision_encoder_public": model_info["vision_encoder_public"],
                "language_backbone_public": model_info["language_backbone_public"],
                "connector_or_resampler_public": model_info["connector_or_resampler_public"],
                "resolution_strategy_public": model_info["resolution_strategy_public"],
                "frame_sampling_public": model_info["frame_sampling_public"],
                "temporal_modeling_public": model_info["temporal_modeling_public"],
                "compression_strategy_public": model_info["compression_strategy_public"],
                "public_visual_token_value": model_info["public_visual_token_value"],
                "public_visual_token_unit": model_info["public_visual_token_unit"],
                "public_visual_token_note": model_info["public_visual_token_note"],
                "token_value_used_for_tpm": model_info["token_value_used_for_tpm"],
                "token_unit_used_for_tpm": model_info["token_unit_used_for_tpm"],
                "token_information_status": model_info["token_information_status"],
                "tpm_estimate": tpm_estimate,
                "encoding_summary": model_info["encoding_summary"],
                "encoding_completeness": model_info["encoding_completeness"],
                "missing_information": model_info["missing_information"],
                "reference_encoding": model_info["reference_encoding"],
                "reference_token": model_info["reference_token"],
            }
        )
    return output_rows


def main() -> None:
    rows = build_rows()
    with OUTPUT_CSV.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=OUTPUT_FIELDS)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Wrote {len(rows)} rows to {OUTPUT_CSV}")


if __name__ == "__main__":
    main()
