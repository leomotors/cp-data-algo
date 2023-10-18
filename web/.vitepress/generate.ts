import fs from "node:fs/promises";
import type { DefaultTheme } from "vitepress";

import { exec as _exec } from "node:child_process";
import { promisify } from "node:util";

const exec = promisify(_exec);

type Builder = (file: string, child: string, date: string) => string;

const extensionOverrides = {
  hpp: "cpp",
  dig: "xml",
};

const allowedExtensions = ["cpp", "hpp", "dig"];

function getCodeContent(content: string) {
  if (!content.includes("region student.h")) {
    return content;
  }

  const regionLines: string[] = [];
  const lines = content.split("\n");

  let i = lines.findIndex((line) => line.includes("region student.h"));

  while (i < lines.length) {
    regionLines.push(lines[i]);

    if (lines[i].includes("endregion")) {
      break;
    }

    i++;
  }

  return regionLines.join("\n");
}

async function createMd(
  file: string,
  folder: string,
  sidebarItems: DefaultTheme.SidebarItem[],
  builder: Builder,
) {
  const tokens = file.split(".");
  const ext = tokens[tokens.length - 1];

  const { stdout: updatedStr } = await exec(
    `git log -1 --pretty="format:%ci" ${folder}/${file}`,
  );

  const fileContent = (await fs.readFile(`${folder}/${file}`))
    .toString()
    .trim();

  fs.writeFile(
    `web/${folder}/${file}.md`,
    builder(
      file,
      `
\`\`\`${extensionOverrides[ext] ?? ext}
${getCodeContent(fileContent)}
\`\`\`
`,
      updatedStr && new Date(updatedStr).toLocaleString("th-TH"),
    ),
  );

  sidebarItems.push({
    text: file,
    link: `/${folder}/${file}`,
  });
}

async function writeFolder(folderName: string, builder: Builder) {
  const sidebarItems: DefaultTheme.SidebarItem[] = [];
  const files = (await fs.readdir(folderName)).filter((file) =>
    allowedExtensions.some((ext) => file.endsWith(ext)),
  );

  for (const file of files) {
    await createMd(file, folderName, sidebarItems, builder);
  }

  await fs.writeFile(
    `web/.vitepress/${folderName}.g.ts`,
    `
  export default ${JSON.stringify(sidebarItems)};
  `,
  );
}

writeFolder(
  "grader",
  (file, child, date) => `
# ${file}

${child}

See on [GitHub](https://github.com/Leomotors/2110211-intro-data-struct/blob/main/grader/${file})

${date && `Last Updated: ${date} (UTC+7)`}
`,
);

writeFolder(
  "quiz",
  (file, child, date) => `
# ${file}

${child}

See on [GitHub](https://github.com/Leomotors/2110211-intro-data-struct/blob/main/grader/${file})

${date && `Last Updated: ${date} (UTC+7)`}
`,
);
